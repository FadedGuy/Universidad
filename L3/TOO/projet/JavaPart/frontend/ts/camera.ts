declare const Quagga: any;

let webSocket: WebSocket;
let wsUrl = "ws://localhost:" + 19992 + "/bc_ws";

function connect() {
    if(webSocket !== undefined && webSocket.readyState !== WebSocket.CLOSED) {
        return;
    }
    console.log("Trying to establish a connection to: " + wsUrl);

    webSocket = new WebSocket(wsUrl);
    
    webSocket.onopen = function() {
        console.log("Connected!");
    };

    webSocket.onmessage = (event: any) => {
        let _nutriScore = window.document.getElementById('nutri') as HTMLDivElement;
        console.log(event.data);
        _nutriScore.textContent = event.data.toUpperCase();
        console.log("onmessage: " + event.data);
    };
    
    webSocket.onclose = function() {
        console.log("Connection closed");
    };
}

function send() {
    let codeTxt = document.getElementById("code") as HTMLDivElement;

    webSocket.send(codeTxt.textContent === null ? "" : codeTxt.textContent);
}

function closeSocket() {
    webSocket.close();
}

connect();

let _DOM_ready = null;
Object.defineProperty(window, "DOM_ready", {
    value: new Promise(launched_function_when_DOM_ready => {
        _DOM_ready = launched_function_when_DOM_ready;
    }), enumerable: false, configurable: false, writable: false
});
window.document.onreadystatechange = _DOM_ready;

(window as any).DOM_ready.then(() => { // DOM is ready as a promise...
    /* Webcam shooting */
    // Tested with Chrome >= 68, Firefox >= 62, Edge >= 42 and Safari >= 11
    // WebRTC camera simple test: https://webrtc.github.io/samples/src/content/getusermedia/gum/
    // HTML tag: '':
    const _my_video = window.document.getElementById('camera_feed') as HTMLVideoElement;
    _my_video.addEventListener('canplay', () => {
        window.console.log("The video is playing...");
        window.console.log("_my_video.videoHeight: " + _my_video.videoHeight + " _my_video.videoWidth: " + _my_video.videoWidth);
    });
    const _working_canvas = window.document.createElement('canvas') as HTMLCanvasElement;

    // window.alert("typeof window.navigator.mediaDevices.getUserMedia: " + typeof window.navigator.mediaDevices.getUserMedia); // 'function'
    // window.alert("Is Promise? " + (window.navigator.mediaDevices.getUserMedia({
    //     audio: false,
    //     video: true
    // }) instanceof Promise)); // 'true'
// Safari: see also "Development" tab, option WebRTC
    /* Not supported by Safari : {video: {width: 512, height: 512, facingMode: 'user'}} */
// Looking at device capabilities:
    // window.alert(JSON.stringify(window.navigator.mediaDevices.getSupportedConstraints()));

    let constraints: {audio: boolean, video: boolean | {facingMode: 'user'}} = {audio: false, video: true};
    if (window.navigator.mediaDevices.getSupportedConstraints().hasOwnProperty('facingMode')) {
        constraints = {audio: false, video: {facingMode: 'user'}}; // Selfie mode...
    }
    // For test:
    // window.navigator.mediaDevices.getUserMedia(constraints).then((stream: MediaStream) => {
    //     _my_video.srcObject = stream; // Assign the webcam to the "my_video" HTML element...
    //     _my_video.play(); // Start playing video...
    // }).catch((error) => {
    //     window.alert("window.navigator.mediaDevices.getUserMedia: " + error.message);
    // });

    const _video_management = () => {
        if (_my_video.srcObject !== null) {
            // Video is running, take photography:
            if ((_my_video.srcObject as MediaStream).getVideoTracks()[0].readyState === 'live') {
                // Before stopping the camera, one records the last frame:
                _working_canvas.setAttribute('width', _my_video.videoWidth.toString());
                _working_canvas.setAttribute('height', _my_video.videoHeight.toString());
                _working_canvas.getContext('2d')!.drawImage(_my_video, 0, 0, _my_video.videoWidth, _my_video.videoHeight);
                const _selfie = new Image();
                _selfie.onload = () => {
                    // This immediately stops the webcam (Firefox keeps the last frame on screen while Chrome generates a black screen):
                    (_my_video.srcObject as MediaStream).getVideoTracks()[0].stop();
                    // The stream is no longer active:
                    window.console.assert((_my_video.srcObject as MediaStream).active === false);
                    window.console.assert((_my_video.srcObject as MediaStream).getVideoTracks()[0].readyState === 'ended');
                    // The stream is detached from the '<video>' tag:
                    _my_video.srcObject = null; // For next shoot...
                    _my_video.setAttribute('poster', _selfie.src);
                };
                _selfie.src = _working_canvas.toDataURL("image/png"); // From canvas to image...
                
                Quagga.decodeSingle({
                    decoder: {
                        readers: ["ean_reader"] // List of active readers
                    },
                    locate: true, // try to locate the barcode in the image
                    src: _working_canvas.toDataURL("image/png") // or 'data:image/jpg;base64,' + data
                }, function(result: any) {
                    const _code_label = window.document.getElementById('code') as HTMLDivElement;
                    if(result.codeResult !== null) {
                        _code_label.textContent = result.codeResult.code;

                        send();
                        console.log("result", result.codeResult.code);
                    } else {
                        _code_label.textContent = "not detected";
                        console.log("not detected");
                    }
                });
            } else  
                window.alert("_my_video.srcObject.getVideoTracks()[0].readyState === 'ended'");
        } else { // New stream is required (with permission?)
            // Firefox asks for permission again...
            window.navigator.mediaDevices.getUserMedia(constraints).then((stream: MediaStream) => {
                // Safari issue here:
                // https://help.milkshake.tv/hc/en-us/articles/115005464689-Videos-not-playing-when-using-Safari-11-web-browser
                _my_video.srcObject = stream; // Assign the webcam to the "my_video" HTML element
                _my_video.play(); // Start playing video...
            }).catch((error) => {
                window.alert("window.navigator.mediaDevices.getUserMedia: " + error.message);
            });
        }
    };

    if (window.PointerEvent) // May not work for some browsers...
        _my_video.onpointerup = _video_management;
    else // Older Safari versions do not support 'window.PointerEvent': https://caniuse.com/#feat=pointer
        _my_video.addEventListener('mouseup', _video_management, true);
});
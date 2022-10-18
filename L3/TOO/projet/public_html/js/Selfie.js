'use strict';

Object.defineProperty(window, "Snapshot", {value: new Promise(send => {
        createjs.Sound.on("fileload", event => {
            send(createjs.Sound.createInstance("./sounds/Snapshot.mp3"));
        });
        createjs.Sound.registerSound("./sounds/Snapshot.mp3", "./sounds/Snapshot.mp3");
    }), enumerable: false, configurable: false, writable: false});

/** DOM ready */
let _DOM_ready = null;
Object.defineProperty(window, "DOM_ready", {value: new Promise(function_launched_when_DOM_ready => {
        _DOM_ready = function_launched_when_DOM_ready;
    }), enumerable: false, configurable: false, writable: false});
document.onreadystatechange = _DOM_ready;

DOM_ready.then(value => { // DOM is ready as a promise...
    /* Webcam shooting **/
    // Tested with Chrome >= 68, Firefox >= 62, Edge >= 42 and Safari >= 11
    // WebRTC camera simple test: https://webrtc.github.io/samples/src/content/getusermedia/gum/
    let _my_video = document.getElementById('my_video'); // HTML tag: '<video id="my_video" width="600" height="800" poster="./img/FranckBarbier.jpg"></video>'
    _my_video.addEventListener('canplay', () => {
        console.log("The video is playing...");
        console.log("_my_video.videoHeight: " + _my_video.videoHeight + " _my_video.videoWidth: " + _my_video.videoWidth);
    });
    let _working_canvas = document.createElement('canvas');

// alert("typeof navigator.mediaDevices.getUserMedia: " + typeof navigator.mediaDevices.getUserMedia); // 'function'
// alert("Is Promise? " + (navigator.mediaDevices.getUserMedia({audio: false, video: true}) instanceof Promise)); // 'true'
// Safari : voir aussi onglet "Développement", option WebRTC
    /* Non supporté par Safari : {video: {width: 512, height: 512, facingMode: "user"}} */
// Looking at device capabilities:
// alert(JSON.stringify(navigator.mediaDevices.getSupportedConstraints()));

    let constraints = {audio: false, video: true};
    if (navigator.mediaDevices.getSupportedConstraints().hasOwnProperty('facingMode')) {
        constraints = {audio: false, video: {facingMode: 'user'}}; // Selfie mode 
    }
//    navigator.mediaDevices.getUserMedia(constraints).then(function (stream) {
//        _my_video.srcObject = stream; // Assign the webcam to the "my_video" HTML element
//        _my_video.play(); // Start playing video...
//    }).catch((error) => {
//        alert("navigator.mediaDevices.getUserMedia: " + error.message);
//    });

    let _video_management = () => {
        if (_my_video.srcObject !== null) {
            if (_my_video.srcObject.getVideoTracks()[0].readyState === "live") { // Video is running, take photo...
                Snapshot.then(sound => {
                    sound.play();
                });
                // Before stopping the camera, one records the last frame:
                _working_canvas.setAttribute('width', _my_video.videoWidth);
                _working_canvas.setAttribute('height', _my_video.videoHeight);
                _working_canvas.getContext('2d').drawImage(_my_video, 0, 0, _my_video.videoWidth, _my_video.videoHeight);
                let _selfie = new Image();
                _selfie.onload = function () {
                    // This immediately stops the webcam (Firefox keeps the last frame on screen while Chrome generates a black screen):
                    _my_video.srcObject.getVideoTracks()[0].stop();
                    // The stream is no longer active:
                    console.assert(_my_video.srcObject.active === false);
                    console.assert(_my_video.srcObject.getVideoTracks()[0].readyState === "ended");
                    // The stream is detached from the '<video>' tag:
                    _my_video.srcObject = null; // For next shoot...
                    _my_video.setAttribute('poster', _selfie.src);
                };
                _selfie.src = _working_canvas.toDataURL("image/png"); // From canvas to image...
                
            } else {
                alert("_my_video.srcObject.getVideoTracks()[0].readyState === \"ended\"");
            }
        } else { // New stream is required (with permission?)
            // Firefox asks for permission again...
            navigator.mediaDevices.getUserMedia(constraints).then(function (stream) {
                // Safari issue here:
                // https://help.milkshake.tv/hc/en-us/articles/115005464689-Videos-not-playing-when-using-Safari-11-web-browser
                _my_video.srcObject = stream; // Assign the webcam to the "my_video" HTML element
                _my_video.play(); // Start playing video...
            }).catch((error) => {
                alert("navigator.mediaDevices.getUserMedia: " + error.message);
            });
        }
    };

    if (window.PointerEvent) // May not work for some browsers...
        _my_video.onpointerup = _video_management;
    else // Safari does not yet support 'window.PointerEvent': https://caniuse.com/#feat=pointer
        _my_video.addEventListener('mouseup', _video_management, true);
});
/** End of DOM ready */

/** Window loaded */
let _Window_loaded = null;
Object.defineProperty(window, "Window_loaded", {value: new Promise(function_launched_when_Window_loaded => {
        _Window_loaded = function_launched_when_Window_loaded;
    }), enumerable: false, configurable: false, writable: false});
window.addEventListener('load', _Window_loaded);

Window_loaded.then(value => {
    window.Snapshot.then(sound => {
        sound.play();
    });
});
/** End of Window loaded */



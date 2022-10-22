window.addEventListener('DOMContentLoaded', (event: Event) => {
    Camera.Run();
});

class Camera {
    static Run(){
        // Could maybe combine video and mediaStream into another class or enum
        const video: HTMLVideoElement = window.document.getElementById("camera_feed") as HTMLVideoElement;
        video.width = 400;
        video.height = 400;
        video.poster = "https://cdn-icons-png.flaticon.com/512/685/685655.png";

        const canvas: HTMLCanvasElement = document.createElement('canvas') as HTMLCanvasElement;
        let mediaStream: MediaStream;

        let constraints = {};
        if(navigator.mediaDevices.getSupportedConstraints().hasOwnProperty('facingMode')){
            constraints = {audio: false, video: {facingMode: 'user'}}; 
        }
        else{
            constraints = {audio: false, video: true};
        }

        let videoManagement = function() {
            if(video.srcObject !== null){
                if(mediaStream.getVideoTracks()[0].readyState === "live"){
                    canvas.setAttribute('width', video.videoWidth.toString());
                    canvas.setAttribute('height', video.videoHeight.toString());
                    canvas.getContext('2d')?.drawImage(video, 0, 0, video.videoWidth, video.videoHeight);
        
                    let selfie = new Image();
                    selfie.onload = function() {
                        mediaStream.getVideoTracks()[0].stop();
                        console.assert(mediaStream.active === false);
                        console.assert(mediaStream.getVideoTracks()[0].readyState === "ended");

                        video.srcObject = null;
                        video.setAttribute('poster', selfie.src);
                    }
                    selfie.src = canvas.toDataURL("image/png");
                }
                else{
                    alert("_my_video.srcObject.getVideoTracks()[0].readyState === \"ended\"");
                }
                
            }
            else{
                navigator.mediaDevices.getUserMedia(constraints)
                    .then(function (stream) {
                        mediaStream = stream;
                        video.srcObject = stream;
                        video.play();
                    })
                    .catch((error) => {
                        alert("navigator.mediaDevices.getUserMedia: " + error.message);
                    });
            }
        }

        if(window.PointerEvent){
            video.onpointerup = videoManagement;
        }
        else{
            video.addEventListener('mouseup', videoManagement, true);
        }
    }
}
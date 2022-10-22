"use strict";
window.addEventListener('DOMContentLoaded', (event) => {
    Camera.Run();
});
class Camera {
    static Run() {
        // Could maybe combine video and mediaStream into another class or enum
        const video = window.document.getElementById("camera_feed");
        video.width = 400;
        video.height = 400;
        video.poster = "https://cdn-icons-png.flaticon.com/512/685/685655.png";
        const canvas = document.createElement('canvas');
        let mediaStream;
        let constraints = {};
        if (navigator.mediaDevices.getSupportedConstraints().hasOwnProperty('facingMode')) {
            constraints = { audio: false, video: { facingMode: 'user' } };
        }
        else {
            constraints = { audio: false, video: true };
        }
        let videoManagement = function () {
            var _a;
            if (video.srcObject !== null) {
                if (mediaStream.getVideoTracks()[0].readyState === "live") {
                    canvas.setAttribute('width', video.videoWidth.toString());
                    canvas.setAttribute('height', video.videoHeight.toString());
                    (_a = canvas.getContext('2d')) === null || _a === void 0 ? void 0 : _a.drawImage(video, 0, 0, video.videoWidth, video.videoHeight);
                    let selfie = new Image();
                    selfie.onload = function () {
                        mediaStream.getVideoTracks()[0].stop();
                        console.assert(mediaStream.active === false);
                        console.assert(mediaStream.getVideoTracks()[0].readyState === "ended");
                        video.srcObject = null;
                        video.setAttribute('poster', selfie.src);
                    };
                    selfie.src = canvas.toDataURL("image/png");
                }
                else {
                    alert("_my_video.srcObject.getVideoTracks()[0].readyState === \"ended\"");
                }
            }
            else {
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
        };
        if (window.PointerEvent) {
            video.onpointerup = videoManagement;
        }
        else {
            video.addEventListener('mouseup', videoManagement, true);
        }
    }
}
//# sourceMappingURL=camera.js.map
import cv2 as cv
import numpy as np

video = cv.VideoCapture("imgs/india.mp4")
cv.namedWindow("video", cv.WINDOW_NORMAL)
fps = int(video.get(cv.CAP_PROP_FPS)) - 2

prev_frame_gris = None
prev_pts = None
trazas = None

while video.isOpened():
    confirmacion, frame = video.read()
    if not confirmacion:
        print("Error al recibir el siguiente frame")
        break

    frame_gris = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    if prev_pts is None:
        prev_pts = cv.goodFeaturesToTrack(frame_gris, 500, 0.05, 10)
        prev_pts = prev_pts.reshape(-1, 1, 2)
    
    pts, status, errors = cv.calcOpticalFlowPyrLK(prev_frame_gris, frame_gris, prev_pts, (15,15), 5, criteria=(cv.TermCriteria_EPS | cv.TermCriteria_MAX_ITER, 10, 10))

    good_pts = pts[status == 1]
    if trazas is None:
        trazas = good_pts
    else:
        trazas = np.vstack((trazas, good_pts))
    
    for p in trazas:
        cv.circle(frame_gris, (p.ravel()), 2, (0,0,0), -1)

    cv.imshow("video", frame_gris)

    key = cv.waitKey(fps)&0xFF
    if key == ord('q'):
        break
    if key == ord('r'):
        trazas = None
        prev_pts = None
    
    prev_frame_gris = frame_gris
    prev_pts = pts


video.release()
cv.destroyAllWindows()
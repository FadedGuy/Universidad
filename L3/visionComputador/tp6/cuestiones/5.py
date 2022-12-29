import cv2 as cv
import numpy as np

video = cv.VideoCapture("imgs/coches.mp4")
cv.namedWindow("video", cv.WINDOW_NORMAL)
n_frames = int(video.get(cv.CAP_PROP_FRAME_COUNT))
cur_frame = 0

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
        pts = cv.goodFeaturesToTrack(frame_gris, 500, 0.05, 10)
        pts = pts.reshape(-1, 1, 2)
    else:
        pts, status, errors = cv.calcOpticalFlowPyrLK(prev_frame_gris, frame_gris, prev_pts, (15,15), 5, criteria=(cv.TermCriteria_EPS | cv.TermCriteria_MAX_ITER, 10, 10))

        good_pts = pts[status == 1]
        if trazas is None:
            trazas = good_pts
        else:
            trazas = np.vstack((trazas, good_pts))
        
        for p in trazas:
            x, y = p.ravel()
            cv.circle(frame_gris, (int(x), int(y)), 2, (255,255,255), -1)


    prev_pts = pts
    prev_frame_gris = frame_gris

    cv.imshow("video", frame_gris)

    print(f"{cur_frame}/{n_frames}")
    cur_frame += 1

    key = cv.waitKey()&0xFF
    if key == ord('q'):
        break
    elif key == ord('r'):
        trazas = None
        prev_pts = None
    
    

video.release()
cv.destroyAllWindows()
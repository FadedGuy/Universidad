import cv2 as cv

img_original = cv.imread("imgs/Ajedrez.jpg")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

esquinas = cv.goodFeaturesToTrack(img_bnw, 20, 0.01, 10)
criterio_stop = (cv.TERM_CRITERIA_MAX_ITER + cv.TermCriteria_EPS, 30, 0.001)
esquinas_final = cv.cornerSubPix(img_bnw, esquinas, (5,5), (-1,-1), criterio_stop)

for esquina in esquinas_final:
    x, y = esquina.ravel()
    cv.circle(img_original, (int(x), int(y)), 2, (255,255,255), -1)

sift = cv.SIFT_create()
kp = sift.detect(img_bnw, None)
img_sift = img_bnw.copy()
img_sift = cv.drawKeypoints(img_bnw, kp, img_sift)

print(cv.__version__)

cv.namedWindow("original", cv.WINDOW_NORMAL)
cv.imshow("original", img_original)
cv.namedWindow("sift", cv.WINDOW_NORMAL)
cv.imshow("sift", img_sift)
cv.waitKey()
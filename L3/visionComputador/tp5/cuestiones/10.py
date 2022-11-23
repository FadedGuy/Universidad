import cv2 as cv

img_original = cv.imread("imgs/Ajedrez.jpg")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

obj_brisk = cv.BRISK_create(125,5)
kp, des = obj_brisk.detectAndCompute(img_bnw, None)

img_salida = cv.drawKeypoints(img_bnw, kp, None, (255,0,0), 4)

cv.namedWindow("ajedrez", cv.WINDOW_NORMAL)
cv.imshow("ajedrez", img_salida)
cv.waitKey()
from turtle import back
import cv2 as cv
import numpy as np

img_original = cv.imread("rice.png", 0)

promedio = cv.GaussianBlur(img_original, (75,75), 75)

background = promedio - promedio.mean()

img_1 = img_original - background
img_1 = img_1/img_1.max()

background = background/background.max()

cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

cv.namedWindow("Thing", cv.WINDOW_NORMAL)
cv.imshow("Thing", promedio)

cv.namedWindow("BG", cv.WINDOW_NORMAL)
cv.imshow("BG", background)

cv.namedWindow("Modif", cv.WINDOW_NORMAL)
cv.imshow("Modif", img_1)

cv.waitKey(0)
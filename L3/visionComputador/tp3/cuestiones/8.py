# Abrimos la imagen rice.png y la mostramos
# Corregimos la iluminacion no homogenea y mostramos la imagen corregida con el background estimado

import cv2 as cv
import matplotlib.pyplot as plt 

# Abrimos la imagen en escala de grises
img_original = cv.imread("rice.png", 0)

# src, filter_size, deviation in X from filter
# Los valores tienen que ser impares y mayor a 0
promedio = cv.GaussianBlur(img_original, (75,75), 75)

background = promedio - promedio.mean()
background = background/background.max()

img_1 = img_original - background
img_1 = img_1/img_1.max()

# Mostramos la imagen original, imagen corregida y el background
cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

cv.namedWindow("BG", cv.WINDOW_NORMAL)
cv.imshow("BG", background)

cv.namedWindow("Corregida", cv.WINDOW_NORMAL)
cv.imshow("Corregida", img_1)

cv.waitKey(0)
cv.destroyAllWindows()

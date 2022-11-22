import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import math

img_original = cv.imread("imgs/Herramientas.JPG")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

img_bnw = cv.medianBlur(img_bnw, 3)
retval, img_binary = cv.threshold(img_bnw, 80, 256, cv.THRESH_BINARY_INV | cv.THRESH_OTSU)
kernel = cv.getStructuringElement(cv.MORPH_RECT, (10,10))
img_binary = cv.dilate(img_binary, kernel)

n_etiquetas, map_etiquetas, stats, centroids = cv.connectedComponentsWithStats(img_binary, 4, cv.CV_32S)
salto = 255//map_etiquetas.max()


# Preparamos la visualizacion y mostramos
for i in range(1, n_etiquetas):
    index = np.where(map_etiquetas==i)
    map_etiquetas[index] = (i)*salto
    cv.putText(map_etiquetas, str(i), (math.trunc(centroids[i][0]), math.trunc(centroids[i][1])), cv.FONT_HERSHEY_PLAIN, 15, 255, 15, cv.LINE_4)

img_etiquetada = cv.normalize(map_etiquetas, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)
cv.namedWindow("etiquetadas", cv.WINDOW_NORMAL)
cv.imshow("etiquetadas", img_etiquetada)
cv.waitKey()
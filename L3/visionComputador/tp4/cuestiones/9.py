import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

# Abrimos y mejoramos y binarizamos la imagen
img_original = cv.imread("imgs/Herramientas.JPG", 0)

img_original = cv.medianBlur(img_original, 3)
retval, img_binary = cv.threshold(img_original, 80, 256, cv.THRESH_BINARY_INV)
kernel = cv.getStructuringElement(cv.MORPH_RECT, (5,5))
img_binary = cv.dilate(img_binary, kernel)

# Etiquetamos los objetos
datos = cv.connectedComponentsWithStats(img_binary, 4, cv.CV_32S)
n_etiquetas, map_etiquetas = datos[0], datos[1]
salto = 255//map_etiquetas.max()

# Preparamos la visualizacion y mostramos
for i in range(n_etiquetas):
    index = np.where(map_etiquetas==i)
    map_etiquetas[index] = (i+1)*salto

plt.imshow(map_etiquetas)
plt.show()

# cv.namedWindow("original", cv.WINDOW_NORMAL)
# cv.namedWindow("binary", cv.WINDOW_NORMAL)
# cv.namedWindow("map", cv.WINDOW_NORMAL)
# cv.imshow("original", img_original)
# cv.imshow("binary", img_binary)
# cv.imshow("map", map_etiquetas)
# cv.waitKey()
# cv.destroyAllWindows()
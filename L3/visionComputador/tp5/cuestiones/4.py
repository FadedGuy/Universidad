import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import math

# Cargamos una imagen 
img_original = cv.imread("imgs/Herramientas.JPG")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

# Eliminamos el ruido, binarizamos la imagen y aplicamos postprocesado para mejorar el resultado binario
img_bnw = cv.medianBlur(img_bnw, 3)
retval, img_binary = cv.threshold(img_bnw, 80, 256, cv.THRESH_BINARY_INV | cv.THRESH_OTSU)
kernel = cv.getStructuringElement(cv.MORPH_RECT, (10,10))
img_binary = cv.dilate(img_binary, kernel)

# Etiquetamos la imagen 
n_etiquetas, map_etiquetas, stats, centroids = cv.connectedComponentsWithStats(img_binary, 4, cv.CV_32S)
salto = 255//map_etiquetas.max()

objetos = list()
# Vamos por cada etiqueta, la marcamos en la imagen y separamos las etiquetas de la imagen
for i in range(1, n_etiquetas):
    index = np.where(map_etiquetas==i)
    map_etiquetas[index] = (i)*salto

    # Recortar al objeto en especiifico
    objeto = np.zeros(img_bnw.shape, np.uint8)
    objeto[index] = img_bnw[index]
    objetos.append(objeto)
    cv.putText(map_etiquetas, str(i), (math.trunc(centroids[i][0]), math.trunc(centroids[i][1])), cv.FONT_HERSHEY_PLAIN, 15, 150, 15, cv.LINE_4)

# Normalizamos el mapa de etiquetas y lo mostramos junto con todos los objetos separados
img_etiquetada = cv.normalize(map_etiquetas, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)
cv.namedWindow("etiquetadas", cv.WINDOW_NORMAL)
cv.imshow("etiquetadas", img_etiquetada)
i = 1
for obj in objetos:
    cv.namedWindow(f"objeto {i}", cv.WINDOW_NORMAL)
    cv.imshow(f"objeto {i}", obj)
    i = i + 1

cv.waitKey()
cv.destroyAllWindows()
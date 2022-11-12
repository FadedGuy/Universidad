import cv2 as cv
import numpy as np

# Utilizamos la misma imagen que en el ejercicio anterior
img_original = cv.imread("imgs/bi_planes.jpg")

# Creamos el filtro laplaciano
kernel = np.array([[0,1,0], [1,-4,1], [0,1,0]], np.float32)

# Aplicamos el filtro y binarizamos la imagen
img_filtro = cv.filter2D(img_original, -1, kernel)
retval, img_binaria = cv.threshold(np.abs(img_filtro), 100, 256, cv.THRESH_BINARY)

# Vemos el resultado
cv.namedWindow("original", cv.WINDOW_NORMAL)
cv.namedWindow("filtro", cv.WINDOW_NORMAL)
cv.namedWindow("umbral", cv.WINDOW_NORMAL)

cv.imshow("original", img_original)
cv.imshow("filtro", img_filtro)
cv.imshow("umbral", img_binaria)
cv.waitKey()
cv.destroyAllWindows()
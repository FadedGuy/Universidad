import cv2 as cv
import numpy as np

# Abrimos la imagen de numeros y umbralizamos
img_original = cv.imread("imgs/Numeros.jpg", 0)
ret, img_binary = cv.threshold(img_original, 110, 256, cv.THRESH_BINARY_INV)

# Encontramos los contornos con findCountours
contour, hier = cv.findContours(img_binary, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)

# Creamos las dos imagenes de salida para contornos internos y externos
img_contou_in = np.zeros(img_original.shape, img_original.dtype)
img_contour_out = np.zeros(img_original.shape, img_original.dtype)

# Verificaremos si un contorno es padre o hijo al revisar si el ultimo indice indica si esta anidado
for i in range(len(contour)):
    if(hier[0][i][3] != -1):
        cv.drawContours(img_contou_in, contour, i, 255, 1)
    else:        
        cv.drawContours(img_contour_out, contour, i, 255, 1)

# Mostramos las imagenes
cv.imshow("before", img_binary)
cv.imshow("inner", img_contou_in)
cv.imshow("outer", img_contour_out)
cv.waitKey()
cv.destroyAllWindows()
# Cargar una imagen
# Eliminar ruido y mejorar contraste si es necesario
# Binarizar la imagen con todas las opciones de aplicacion de umbral en cv2.threshold
# Mostrar cada una de las salidas y explicar porque cada una de ellas se corresponde con el tipo de umbralizacion
# Volver a binarizar la imagen con una de las opciones de umbral añadiendo el algoritmo de Otsu. Que valor de umbral ha calculado el algoritmo?

import cv2 as cv
import matplotlib.pyplot as plt

# Cargamos una imagen
img_original = cv.imread("imgs/Grapadora.JPG", 0)

# Umbral estimado a partir del histograma
# histograma = cv.calcHist([img_original], [0], None, [256], [0, 256])
# plt.plot(histograma)
# plt.show()
umbral_estimado = 110

# Binarizacion y usos de threshold
retval_binary, img_binary = cv.threshold(img_original, umbral_estimado, 256, type=cv.THRESH_BINARY)
retval_binary_inv, img_binary_inv = cv.threshold(img_original, umbral_estimado, 256,type=cv.THRESH_BINARY_INV)
retval_trunc, img_trunc = cv.threshold(img_original, umbral_estimado, 256,type=cv.THRESH_TRUNC)
retval_tozero, img_tozero = cv.threshold(img_original, umbral_estimado, 256,type=cv.THRESH_TOZERO)
retval_tozero_inv, img_tozero_inv = cv.threshold(img_original, umbral_estimado, 256,type=cv.THRESH_TOZERO_INV)

retval_otsu, img_otsu = cv.threshold(img_original, umbral_estimado, 256, type=cv.THRESH_OTSU)
# Umbrales de las imagenes y el estimado por otsu al final
# print(f"{retval_binary}, {retval_otsu}")

cv.imshow("original", img_original)

# Mostramos todas las imagenes
cv.imshow("binary", img_binary)
cv.imshow("binary inv", img_binary_inv)
cv.imshow("trunc", img_trunc)
cv.imshow("tozero", img_tozero)
cv.imshow("tozero inv", img_tozero_inv)
cv.imshow("otsu", img_otsu)
cv.waitKey(0)
cv.destroyAllWindows()


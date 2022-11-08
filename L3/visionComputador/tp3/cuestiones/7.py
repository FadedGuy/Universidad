# Cargar una imagen y mostrar su histograma
# Programar una funcion de mejora de contraste 
# Aplicar a la imagen una ecualizacion del histograma
# Aplicar a la imagen original una ecualizacion adaptativa
# Mostrar la imagen original, el histograma inicial y las cinco imagenes de salida

import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np

# Expansion del histograma. Tomara p1 y p2 por default a menos que se especifique
def expandHist(img, gamma, p1 = 0, p2 = 255):
    aux = np.maximum(img, p1)
    aux2 = np.minimum(aux, p2)

    sub = np.subtract(aux2, p1)
    img2 = np.true_divide(sub, (p2-p1))

    img3 = np.power(img2, gamma)

    return img3

# Cargar una imagen
img_original = cv.imread("rice.png", 0)

# Obtener el histograma
histograma_inicial = cv.calcHist([img_original], [0], None, [256], [0,256])

img_propio1 = expandHist(img_original, 1)
img_propio2 = expandHist(img_original, 1.5)
img_propio3 = expandHist(img_original, 0.5)

# Ecualizacion del histograma 
img_equalize = cv.equalizeHist(img_original)

# El limite para limitar el constrate, tama;o de la cuadricula a equalizar
clahe_ctrl = cv.createCLAHE(50, [8,8])
# Ecualizacion adaptativa
img_clahe = clahe_ctrl.apply(img_original)

# Mostramos las imagenes
cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

cv.namedWindow("Propio Manteniendo", cv.WINDOW_NORMAL)
cv.imshow("Propio Manteniendo", img_propio1)

cv.namedWindow("Propio Incrementando", cv.WINDOW_NORMAL)
cv.imshow("Propio Incrementando", img_propio2)

cv.namedWindow("Propio Disminuyendo", cv.WINDOW_NORMAL)
cv.imshow("Propio Disminuyendo", img_propio3)

cv.namedWindow("Equilizada", cv.WINDOW_NORMAL)
cv.imshow("Equilizada", img_equalize)

cv.namedWindow("Clahe", cv.WINDOW_NORMAL)
cv.imshow("Clahe", img_clahe)

cv.waitKey(0)
cv.destroyAllWindows()

# Mostramos el histograma inicial
plt.title("Histograma Inicial")
plt.plot(histograma_inicial)
plt.show()


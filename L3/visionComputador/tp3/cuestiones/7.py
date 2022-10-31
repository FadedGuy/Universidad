import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np

def expandHist(img, p1, p2, gamma):
    aux = np.maximum(img, p2)
    aux2 = np.minimum(aux, p1)

    sub = np.subtract(aux2, p1)
    img2 = np.true_divide(sub, (p2-p1))

    img3 = np.power(img2, gamma)

    return img3

img_original = cv.imread("rice.png", 0)

histograma_inicial = cv.calcHist([img_original], [0], None, [256], [0,256])

img_propio = expandHist(img_original, 125, 150, 1)

img_equalize = cv.equalizeHist(img_original)

# El limite para limitar el constrate, tama;o de la cuadricula a equalizar
clahe_ctrl = cv.createCLAHE(50, [8,8])
img_clahe = clahe_ctrl.apply(img_original)

cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

cv.namedWindow("Propio", cv.WINDOW_NORMAL)
cv.imshow("Propio", img_propio)

cv.namedWindow("Equilizada", cv.WINDOW_NORMAL)
cv.imshow("Equilizada", img_equalize)

cv.namedWindow("Clahe", cv.WINDOW_NORMAL)
cv.imshow("Clahe", img_clahe)

cv.waitKey(0)

# plt.plot(histograma_inicial)
# plt.show()


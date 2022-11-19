import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np
from enum import Enum

class Imagenes(Enum):
    ALL1 = "combinacion1.jpg"
    ALL2 = "combinacion2.jpg"
    GOMA1 = "goma1.jpg"
    GOMA2 = "goma2.jpg"
    LAPIZ1 = "lapiz1.jpg"
    LAPIZ2 = "lapiz2.jpg"
    ROT1 = "rotulador1.jpg"
    ROT2 = "rotulador2.jpg"


def func(_val):
    img_original = cv.imread(_val)

    img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

    # Equalizamos la imagen en blanco y negro para resultar los objetos lo mas posible
    img_limpia = cv.equalizeHist(img_bnw)
    # Eliminamos el ruido causado por la ecualizacion y de la imagen misma
    # img_limpia = cv.medianBlur(img_limpia, 25)
    img_limpia = cv.GaussianBlur(img_limpia, (25,25), 25)

    # Para obtener el umbral optimo
    # histograma = cv.calcHist([img_limpia], [0], None, [256], [0, 256])
    # plt.plot(histograma)
    # plt.show()

    # 40 valor mas optimo
    retval, img_binaria = cv.threshold(img_limpia, 40, 255, type=cv.THRESH_BINARY_INV)
    # retval, img_binaria = cv.threshold(img_limpia, 40, 255, type=cv.THRESH_BINARY_INV+cv.THRESH_OTSU)

    # Pasamos de nuevo un filtro de mediana en el caso que el umbral no haya sido el mas optimo
    img_binaria_limpia = cv.medianBlur(img_binaria, 25)

    kernel = cv.getStructuringElement(cv.MORPH_RECT, (15,15))
    img_binaria_limpia = cv.morphologyEx(img_binaria_limpia, cv.MORPH_CLOSE, kernel)
    # img_binaria_limpia = cv.dilate(img_binaria_limpia, kernel)

    return img_original, img_binaria_limpia

# for img in list(Imagenes):
#     img_original, img_clean = func(f"imgs/{img.value}")

#     cv.namedWindow(f"Original {img.name}", cv.WINDOW_NORMAL)
#     cv.imshow(f"Original {img.name}", img_original)
    
#     cv.namedWindow(f"After {img.name}", cv.WINDOW_NORMAL)
#     cv.imshow(f"After {img.name}", img_clean)

img_original, img_clean = func(f"imgs/{Imagenes.LAPIZ2.value}")

cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

# cv.namedWindow("Original BnW", cv.WINDOW_NORMAL)
# cv.imshow("Original BnW", img_bnw)

# cv.namedWindow("Clean", cv.WINDOW_NORMAL)
# cv.imshow("Clean", img_limpia)

# cv.namedWindow("Binaria", cv.WINDOW_NORMAL)
# cv.imshow("Binaria", img_binaria)

cv.namedWindow("Binaria Clean", cv.WINDOW_NORMAL)
cv.imshow("Binaria Clean", img_clean)

cv.waitKey()
cv.destroyAllWindows()
import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np
from enum import Enum
import math

class Imagenes(Enum):
    ALL1 = "ALL1.jpg"
    ALL2 = "ALL2.jpg"
    GOMA1 = "GOMA1.jpg"
    GOMA2 = "GOMA2.jpg"
    LAPIZ1 = "LAPIZ1.jpg"
    LAPIZ2 = "LAPIZ2.jpg"
    ROT1 = "ROT1.jpg"
    ROT2 = "ROT2.jpg"

def expandHist(img, gamma, p1 = 0, p2 = 255):
    aux = np.maximum(img, p1)
    aux2 = np.minimum(aux, p2)

    sub = np.subtract(aux2, p1)
    img2 = np.true_divide(sub, (p2-p1))

    img3 = np.power(img2, gamma)

    return img3

def binarizar(img):
    # Equalizamos la imagen en blanco y negro para resultar los objetos lo mas posible
    img_limpia = cv.GaussianBlur(img, (25,25), 25, cv.BORDER_CONSTANT)
    img_limpia = expandHist(img, 0.4)

    # img_limpia = cv.equalizeHist(img_limpia)
    # Para obtener el umbral optimo
    # histograma = cv.calcHist([img_limpia], [0], None, [256], [0, 256])
    # plt.plot(histograma)
    # plt.show()
    img_limpia = cv.normalize(img_limpia, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)
    # 40 valor mas optimo
    retval, img_binaria = cv.threshold(img_limpia, 80, 255, type=cv.THRESH_BINARY_INV|cv.THRESH_OTSU)
    # img_binaria = cv.adaptiveThreshold(img_limpia, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY_INV, 5, 2)

    cv.namedWindow("hi", cv.WINDOW_NORMAL)
    cv.imshow("hi", img_limpia)
    cv.waitKey()

    # Pasamos de nuevo un filtro de mediana en el caso que el umbral no haya sido el mas optimo
    img_binaria_limpia = cv.medianBlur(img_binaria, 25)

    kernel = cv.getStructuringElement(cv.MORPH_RECT, (55,55))
    img_binaria_limpia = cv.erode(img_binaria_limpia, kernel)
    img_binaria_limpia = cv.morphologyEx(img_binaria_limpia, cv.MORPH_CLOSE, kernel)

    return img_binaria_limpia

def contours(img_draw, img_binary):
    a_contours, hierachy = cv.findContours(img_binary, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)
    cv.drawContours(img_draw, a_contours, -1, 150, 15)

    for i in range(len(a_contours)):
        cv.putText(img_draw, str(i), (a_contours[i][0][0][0], a_contours[i][0][0][1]), cv.FONT_HERSHEY_PLAIN, 20, (0,0,0), 15, cv.LINE_4)

    return img_draw

def etiquetas(img_draw, img_binary):
    n_etiquetas, map_etiquetas, stats, centroids = cv.connectedComponentsWithStats(img_binary, 4, cv.CV_32S)
    salto = 255//map_etiquetas.max()

    objetos = list()
    for i in range(1, n_etiquetas):
        index = np.where(map_etiquetas==i)
        img_draw[index] = (i)*salto

        # Recortar al objeto en especiifico
        objeto = np.zeros(img_draw.shape, np.uint8)
        objeto[index] = img_draw[index]
        objetos.append(objeto)

        cv.putText(img_draw, str(i), (math.trunc(centroids[i][0]), math.trunc(centroids[i][1])), cv.FONT_HERSHEY_PLAIN, 15, 150, 15, cv.LINE_4)

    img_etiquetada = cv.normalize(img_draw, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)

    return img_etiquetada, objetos

def procesar(_val):
    img_original = cv.imread(_val)

    img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

    img_binary = binarizar(img_bnw)
    img_contour = contours(img_original.copy(), img_binary)
    img_tag, tag_imgs = etiquetas(img_original.copy(), img_binary)

    return img_original, img_binary, img_contour, img_tag, tag_imgs

# fila, columna = 7, 4
# fig = plt.figure(figsize=(fila, columna))
# i = 1
# for img in list(Imagenes):
#     img_original, img_clean = binarizar(f"imgs/{img.value}")

#     fig.add_subplot(fila, columna, i)
#     plt.imshow(img_original, cmap='gray')

#     fig.add_subplot(fila, columna, i+1)
#     plt.imshow(img_clean, cmap='gray')

#     i = i+2

    # cv.namedWindow(f"Original {img.name}", cv.WINDOW_NORMAL)
    # cv.imshow(f"Original {img.name}", img_original)
    
    # cv.namedWindow(f"After {img.name}", cv.WINDOW_NORMAL)
    # cv.imshow(f"After {img.name}", img_clean)
# plt.show()

img_original, img_binary, img_contour, img_tag, tag_imgs = procesar(f"imgs/{Imagenes.LAPIZ2.value}")

# fig.add_subplot(fila, columna, 1)
# plt.imshow(img_original, cmap='gray')
# fig.add_subplot(fila, columna, 2)
# plt.imshow(img_binary, cmap='gray')
# fig.add_subplot(fila, columna, 3)
# plt.imshow(img_contour, cmap='gray')
# fig.add_subplot(fila, columna, 4)
# plt.imshow(img_tag, cmap='gray')

cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

cv.namedWindow("Binaria Clean", cv.WINDOW_NORMAL)
cv.imshow("Binaria Clean", img_binary)

cv.namedWindow("Contornos", cv.WINDOW_NORMAL)
cv.imshow("Contornos", img_contour)

cv.namedWindow("Etiquetas", cv.WINDOW_NORMAL)
cv.imshow("Etiquetas", img_tag)

i = 5
for obj in tag_imgs:
    cv.namedWindow(f"objeto {i}", cv.WINDOW_NORMAL)
    cv.imshow(f"objeto {i}", obj)
    # fig.add_subplot(fila, columna, i)
    # plt.imshow(obj, cmap='gray')

    i = i + 1

# plt.show()
cv.waitKey()
cv.destroyAllWindows()
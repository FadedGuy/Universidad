import cv2 as cv
import numpy as np
import math
from enum import Enum
from MiLib import CalculoLBP, codigoCadena

class Imagenes(Enum):
    ALL1 = "ALL1.jpg"
    ALL2 = "ALL2.jpg"
    GOMA1 = "GOMA1.jpg"
    GOMA2 = "GOMA2.jpg"
    LAPIZ1 = "LAPIZ1.jpg"
    LAPIZ2 = "LAPIZ2.jpg"
    ROT1 = "ROT1.jpg"
    ROT2 = "ROT2.jpg"

# Funcion de mejora de contraste manteniendo o modificando el brillo (tema3 cuestion7)
def expandHist(img, gamma, p1 = 0, p2 = 255):
    aux = np.maximum(img, p1)
    aux2 = np.minimum(aux, p2)

    sub = np.subtract(aux2, p1)
    img2 = np.true_divide(sub, (p2-p1))

    img3 = np.power(img2, gamma)

    return img3


def binarizar(img):
    # Aplicamos un poco de preprocesado para el ruido y expandiendo el histograma teniendo la imagen con una mayor distincion
    img_limpia = cv.GaussianBlur(img, (25,25), 25, cv.BORDER_CONSTANT)
    img_limpia = expandHist(img, 0.8)
    img_limpia = cv.normalize(img_limpia, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)

    # Binarizamos la imagen por y agregamos otsu como argumento
    retval, img_binaria = cv.threshold(img_limpia, 1, 255, type=cv.THRESH_BINARY|cv.THRESH_OTSU)

    # Pasamos de nuevo un filtro de mediana en el caso que el umbral no haya sido el mas optimo y haya un poco de ruido
    img_binaria_limpia = cv.medianBlur(img_binaria, 25)

    # Postprocesado para cerrar contornos y rellenar dentro de un objeto
    kernel = cv.getStructuringElement(cv.MORPH_RECT, (25,25))
    img_binaria_limpia = cv.dilate(img_binaria_limpia, kernel)
    img_binaria_limpia = cv.morphologyEx(img_binaria_limpia, cv.MORPH_CLOSE, kernel)

    return img_binaria_limpia


def etiquetas(img_draw, img_binary):
    # Etiquetas
    n_etiquetas, map_etiquetas, stats, centroids = cv.connectedComponentsWithStats(img_binary, 4, cv.CV_32S)
    salto = 255//map_etiquetas.max()

    objetos = list()
    # Empezamos de 1 para no etiquetar el fondo
    for i in range(1, n_etiquetas):
        index = np.where(map_etiquetas==i)
        # Recortar al objeto en especifico con los pixeles de la imagen original 
        objeto = np.zeros(img_draw.shape, np.uint8)
        objeto[index] = img_draw[index]
        objetos.append(objeto)
        
        img_draw[index] = (i)*salto
        
        # Agregamos el texto dle numero de etiqueta que es
        cv.putText(img_draw, str(i), (math.trunc(centroids[i][0]), math.trunc(centroids[i][1])), cv.FONT_HERSHEY_PLAIN, 15, 150, 15, cv.LINE_4)

    img_etiquetada = cv.normalize(img_draw, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)

    return img_etiquetada, objetos


def procesar(_val):
    img_original = cv.imread(_val)

    img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

    img_binary = binarizar(img_bnw)
    img_tag, tag_imgs = etiquetas(img_original.copy(), img_binary)

    return img_original, img_tag, tag_imgs


def medidas(_img):
    img_bnw = cv.cvtColor(_img, cv.COLOR_BGR2GRAY)
    countours, hierarchy = cv.findContours(img_bnw, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)

    (xx, yy), (MA, ma), angle = cv.fitEllipse(countours[0])

    # cv.drawContours(img_bnw, countours,-1, 170, 5)
    # cv.namedWindow("huh", cv.WINDOW_NORMAL)
    # cv.imshow("huh", img_bnw)
    # cv.waitKey()
    scale_percent = 10 # percent of original size
    width = int(img_bnw.shape[1] * scale_percent / 100)
    height = int(img_bnw.shape[0] * scale_percent / 100)
    dim = (width, height)
    img_resized = cv.resize(img_bnw, dim, interpolation=cv.INTER_AREA)

    area = cv.contourArea(countours[0])
    cc = codigoCadena(countours[0])
    elongacion = MA/ma
    lbp = CalculoLBP(img_resized)
    huMoments = cv.HuMoments(cv.moments(countours[0]))

    envolturas = cv.convexHull(countours[0])
    solidez = area / cv.contourArea(envolturas)

    with open("res.txt", 'a') as file:
        file.write(f"{area}")

        file.write(",[")
        for c in cc:
            file.write(f"{c} ")
        file.write("],")
        
        file.write(f"{elongacion}")
        file.write(",[")

        for lb in lbp:
            file.write(f"{lb}")
        file.write("],[")

        for moment in huMoments:
            file.write(f"{moment}")
        file.write("],")
        file.write(f"{solidez}\n")


img_original, img_tag, tag_imgs = procesar(f"imgs/{Imagenes.ALL2.value}")

cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

cv.namedWindow("Etiqueta", cv.WINDOW_NORMAL)
cv.imshow("Etiqueta", img_tag)

i = 0
# medidas(tag_imgs[i])
for obj in tag_imgs:
    cv.namedWindow(f"objeto {i}", cv.WINDOW_NORMAL)
    cv.imshow(f"objeto {i}", obj)
    medidas(obj)
    i = i + 1

cv.waitKey()
cv.destroyAllWindows()
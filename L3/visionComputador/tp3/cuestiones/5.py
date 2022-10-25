# Cargar una imagen
# Agregar ruido salt&pepper y gaussiano de la libreria Ruido.py
# Eliminar el ruido con un filtro de promediado usando filter2D
# Eliminar el ruido con un filtro gaussiano
# Eliminar el ruido con un filtro de mediana
# Mostrar la imagen original, la imagen con ruido, y las 3 de ruido

import cv2 as cv
import Ruido

# Cargar una imagen en b&w
img_original = cv.imread("img.jpg", 0)

# Agregamos ruido "falso" a la imagen
img_ruido = Ruido.SalyPimienta(img_original)
# img_ruido = Ruido.RuidoGaussiano(img_original, .3)

# Eliminamos el ruido por medio del filtro promediado
img_promediado = cv.blur(img_ruido, (3,3))

# Eliminamos el ruido con un filtro gaussiano
img_gauss = cv.GaussianBlur(img_ruido, (3,3), 3)

# Eliminamos el ruido por meddiana
img_mediana = cv.medianBlur(img_ruido, 3)

# Mostramos las imagenes
cv.namedWindow("Imagen Original", cv.WINDOW_NORMAL)
cv.imshow("Imagen Original", img_original)

cv.namedWindow("Imagen Salt & Pepper", cv.WINDOW_NORMAL)
cv.imshow("Imagen Salt & Pepper", img_ruido)

cv.namedWindow("Imagen Promediado", cv.WINDOW_NORMAL)
cv.imshow("Imagen Promediado", img_promediado)

cv.namedWindow("Imagen Gaussiano", cv.WINDOW_NORMAL)
cv.imshow("Imagen Gaussiano", img_gauss)

cv.namedWindow("Imagen Mediana", cv.WINDOW_NORMAL)
cv.imshow("Imagen Mediana", img_mediana)

cv.waitKey(0)
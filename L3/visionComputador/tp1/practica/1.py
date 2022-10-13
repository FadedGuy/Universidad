# Abrir y mostrar una imagen
# Añadir una linea, circulo y rectangulo a la imagen y mostrarlo
# Añadir una elipse y texto a la imagen original y mostrarla
import cv2 as cv

img = cv.imread("pato.jpg")
img_1 = img.copy()

# Abrir y mostrar una imagen
cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img)

# Añadir una linea, circulo y rectangulo
#img, xyInicio, xyFin, rgbColor, grosor, tipo linea
cv.line(img_1, (500,500), (550, 1500), (0, 255, 0), 10, cv.LINE_AA)
#img, xyCentro, radio, rgbColor, grosor, tipo linea
cv.circle(img_1, (900, 850), 200, (255,255,0), 20, cv.LINE_4)
#img, xyEsquina, xyEsquina2, rgbColor, grosor, tipo linea
cv.rectangle(img_1, (1500,500), (2500, 800), (0, 255, 255), 15, cv.LINE_AA)
# cv.rectangle(img_1, (15, 20, 900, 400), (0, 255, 255), 15, cv.LINE_AA)

cv.namedWindow("Modificada", cv.WINDOW_NORMAL)
cv.imshow("Modificada", img_1)

# Añadir una elipse y texto 
#img, rectanguloRotado(xy1, xy2, angulo), rgbColor, grosor, tipo linea
cv.ellipse(img, (1500, 1500), (75, 400), 87.1, 0, 360, (255,0,0), 15, cv.LINE_8)
# cv.ellipse(img, ((150, 150), (750,400), 60), (0,255, 0))
#img, text, xyOrigen, tipo fuente, escala fuente, rgbColor, grosor, tipo linea
cv.putText(img, "Este es un texto", (150, 800), cv.FONT_HERSHEY_PLAIN, 16, (0,255,0), 15, cv.LINE_4)

cv.namedWindow("Original modificada", cv.WINDOW_NORMAL)
cv.imshow("Original modificada", img)

cv.waitKey(0)&0xFF
cv.destroyAllWindows()
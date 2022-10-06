# Cargar una imagen
# Obtener el negativo restando 255 a el valor de cada pixel
# Aplicar un umbral >p<, todos cuya intensidad sea menor a p se pone a 0 y mayor a 255
from decimal import ROUND_HALF_DOWN
import cv2 as cv
import numpy as np

# Cargar una imagen
img = cv.imread("img.jpg")
if img is None:
    print("No se pudo leer la imagen")
    exit()

img_bnw = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
_img_bnw = img_bnw
# cv.imshow("image", img)
# cv.waitKey(0)

# Obtener el negativo restando 255 al valor de cada pixel
# for i in range(img.shape[0]):
#     for j in range(img.shape[1]):
#         img_bnw[i,j] = 255 - img_bnw[i,j] 
#         r,g,b = img[i,j]
#         img[i,j] = [255-r, 255-g, 255-b]

# cv.imshow("image", img)
# cv.imshow("image bnw", img_bnw)
# cv.waitKey(0)

# Aplicar un umbral p
p = 123
for i in range(_img_bnw.shape[0]):
    for j in range(_img_bnw.shape[1]):
        if _img_bnw[i, j] < p:
            _img_bnw[i,j] = 0
        else:
            _img_bnw[i,j] = 255
    
cv.imshow("umbral", _img_bnw)
cv.waitKey(0)
cv.destroyAllWindows()
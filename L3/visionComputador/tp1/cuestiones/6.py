# Cargar una imagen
# Obtener el negativo restando 255 a el valor de cada pixel
# Aplicar un umbral >p<, todos cuya intensidad sea menor a p se pone a 0 y mayor a 255
import cv2 as cv
import numpy as np

# Cargar una imagen
img = cv.imread("img.jpg")
if img is None:
    print("No se pudo leer la imagen")
    exit()

# Podemos convertir la imagen a blanco y negro post haberla cargado
img_bnw = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
_img_bnw = img_bnw

# cv.namedWindow("image", cv.WINDOW_NORMAL) 
# cv.imshow("image", img)
# cv.waitKey(0)

# Iterativamente sobre la misma imagen
# Obtener el negativo restando 255 al valor de cada pixel
# for i in range(img.shape[0]):
#     for j in range(img.shape[1]):
#         img_bnw[i,j] = 255 - img_bnw[i,j] 
#         r,g,b = img[i,j]
#         img[i,j] = [255-r, 255-g, 255-b]

# Usando una matriz numpy
img_bnw_out = np.ones(img_bnw.shape, np.uint8)
img_bnw_out = 255 - img_bnw

# cv.namedWindow("image", cv.WINDOW_NORMAL)
# cv.imshow("image", img)
cv.namedWindow("image bnw", cv.WINDOW_NORMAL)
cv.imshow("image bnw", img_bnw_out)
cv.waitKey(0)

# Aplicar un umbral p
p = 123
for i in range(_img_bnw.shape[0]):
    for j in range(_img_bnw.shape[1]):
        if _img_bnw[i, j] < p:
            _img_bnw[i,j] = 0
        else:
            _img_bnw[i,j] = 255
    
cv.namedWindow("umbral", cv.WINDOW_NORMAL)
cv.imshow("umbral", _img_bnw)
cv.waitKey(0)&0xFF
cv.destroyAllWindows()
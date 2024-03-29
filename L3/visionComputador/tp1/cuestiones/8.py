# Crear una matriz 3x3 cuyos elementos sean todos igual a 1/9. esta coincide con un filtro 
# promediado en un entorno de vecindad 8
# Aplicar el filtro a la imagen con la funcion filter2D y ver el resultado
import cv2 as cv
import numpy as np

image = cv.imread("Chin1.JPG", 0)
if image is None:
    print("Unable to read image")
    exit()

image = cv.resize(image, (700, 931))

# Matriz 3x3 todos los elementos igual a 1/9 (Usada cuando se ponen distintos valores)
# kernel = np.array([
#     [1/9, 1/9, 1/9],
#     [1/9, 1/9, 1/9],
#     [1/9, 1/9, 1/9]    
# ])

# Otra manera de crear una matriz 3x3 igual a 1/9 (Usada cuando se tiene el mismo valor)
kernel = np.ones((3,3))/9

# src, ddepth = -1, kernel
res_img = cv.filter2D(image, -1, kernel)

cv.namedWindow("Image", cv.WINDOW_NORMAL)
cv.namedWindow("Resultado", cv.WINDOW_NORMAL)
cv.imshow("Image", image)
cv.imshow("Resultado", res_img)
cv.waitKey(0)
cv.destroyAllWindows()
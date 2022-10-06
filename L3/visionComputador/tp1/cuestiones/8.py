# Crear una matriz 3x3 cuyos elementos sean todos igual a 1/9. esta coincide con un filtro 
# promediado en un entorno de vecindad 8
# Aplicar el filtro a la imagen con la funcion filter2D y ver el resultado
import cv2 as cv
import numpy as np

image = cv.imread("chin1.jpg", 0)
if image is None:
    print("Unable to read image")
    exit()

# Matriz 3x3 todoslos elementos igual a 1/9
filter = np.array([
    [1/9, 1/9, 1/9],
    [1/9, 1/9, 1/9],
    [1/9, 1/9, 1/9]    
])

# src, ddepth = -1, kernel
res_img = cv.filter2D(image, -1, filter)

cv.imshow("Image", image)
cv.imshow("Resultado", res_img)
cv.waitKey(0)
cv.destroyAllWindows()
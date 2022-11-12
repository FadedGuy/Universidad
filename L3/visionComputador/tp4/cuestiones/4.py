import cv2 as cv

# Imagen binarizada del ejercicio 2
img_original = cv.imread("imgs/binary.png")

# Obtengo mi elemento estructural de 3x3
kernel = cv.getStructuringElement(cv.MORPH_RECT, (3,3))
# kernel = cv.getStructuringElement(cv.MORPH_CROSS, (3,3))
# kernel = cv.getStructuringElement(cv.MORPH_ELLIPSE, (3,3))

# Aplicamos las 4 operaciones morfologicas 
img_erode = cv.erode(img_original, kernel) 
img_dilate = cv.dilate(img_original, kernel) 
img_close = cv.morphologyEx(img_original, cv.MORPH_CLOSE, kernel) 
img_open = cv.morphologyEx(img_original, cv.MORPH_OPEN, kernel) 


# Mostramos las 5 imagenes
cv.imshow("original", img_original)
cv.imshow("erode", img_erode)
cv.imshow("dilate", img_dilate)
cv.imshow("close", img_close)
cv.imshow("open", img_open)
cv.waitKey()
cv.destroyAllWindows()

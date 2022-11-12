import cv2 as cv
import numpy as np

# Cargamos la imagen de la base de datos de dos objetos
img_original = cv.imread("imgs/bi_planes.jpg")

# Creamos los filtros de Sobel
sob_y = np.array([[-1,0,1], [-2,0,2], [-1,0,1]], np.float32)
sob_x = np.array([[-1,-2,-1], [0,0,0], [1,2,1]], np.float32)

# Aplicamos dichos filtros a la imagen y las sumamos
img_gx = cv.filter2D(img_original, -1, sob_x)
img_gy = cv.filter2D(img_original, -1, sob_y)

img_gxy = img_gx + img_gy

# Usando el valor absoluto, binarizamos las imagenes
retval_x, img_x = cv.threshold(np.abs(img_gx), 110, 255, cv.THRESH_BINARY)
retval_y, img_y = cv.threshold(np.abs(img_gy), 80, 255, cv.THRESH_BINARY)
retval_xy, img_xy = cv.threshold(np.abs(img_gxy), 110, 255, cv.THRESH_BINARY)

# Un poco de procesado para definir bien los bordes y usando cierre
kernel = cv.getStructuringElement(cv.MORPH_RECT, (3,3))
img_x = cv.morphologyEx(img_x, cv.MORPH_CLOSE, kernel)
img_y = cv.morphologyEx(img_y, cv.MORPH_CLOSE, kernel)
img_xy = cv.morphologyEx(img_xy, cv.MORPH_CLOSE, kernel)

# Aplicamos Canny a las imagenes
canny_x = cv.Canny(img_x, 100, 200)
canny_y = cv.Canny(img_y, 100, 200)
canny_xy = cv.Canny(img_xy, 100, 200)


# Visualizamos las imagenes
cv.namedWindow("original", cv.WINDOW_NORMAL)
# cv.namedWindow("gx", cv.WINDOW_NORMAL)
# cv.namedWindow("gy", cv.WINDOW_NORMAL)
# cv.namedWindow("gxy", cv.WINDOW_NORMAL)
# cv.namedWindow("b gx", cv.WINDOW_NORMAL)
# cv.namedWindow("b gy", cv.WINDOW_NORMAL)
# cv.namedWindow("b gxy", cv.WINDOW_NORMAL)
cv.namedWindow("canny x", cv.WINDOW_NORMAL)
cv.namedWindow("canny y", cv.WINDOW_NORMAL)
cv.namedWindow("canny xy", cv.WINDOW_NORMAL)

cv.imshow("original", img_original)
# cv.imshow("gx", img_gx)
# cv.imshow("gy", img_gy)
# cv.imshow("gxy", img_gxy)
# cv.imshow("b gx", img_x)
# cv.imshow("b gy", img_y)
# cv.imshow("b gxy", img_xy)
cv.imshow("canny x", canny_x)
cv.imshow("canny y", canny_y)
cv.imshow("canny xy", canny_xy)
cv.waitKey()
cv.destroyAllWindows()
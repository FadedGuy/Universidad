import cv2 as cv

# Cargamos la imagen y transformamos en blanco y negro
img_original = cv.imread("imgs/Cuadrados.jpg")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

# Aplicamos la funcion de deteccion de esquinas
maxCorners = 20
esquinas = cv.goodFeaturesToTrack(img_bnw, maxCorners, 0.01, 10)

# Definimos el criterio de stop para la precision subpixel y lo aplicamos
criterio_stop = (cv.TERM_CRITERIA_MAX_ITER + cv.TERM_CRITERIA_EPS, maxCorners, 0.0001)
esquinas_final = cv.cornerSubPix(img_bnw, esquinas, (5,5), (2,2), criterio_stop)

# Dibujamos sobre la imagen 
for esquina in esquinas_final:
    x, y = esquina.ravel()
    cv.circle(img_original, (int(x), int(y)), 2, (0,0,0), -1)


cv.namedWindow("original", cv.WINDOW_NORMAL)
cv.imshow("original", img_original)
cv.waitKey()
cv.destroyAllWindows()
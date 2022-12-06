import cv2 as cv

# Cargamos una imagen y la transformamos en blanco y negro
img_original = cv.imread("imgs/Ajedrez.jpg")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

# Creamos un objeto BRISK
obj_brisk = cv.BRISK_create(125,5)
# Buscamos los puntos de interes 
kp, des = obj_brisk.detectAndCompute(img_bnw, None)
# Dibujamos los puntos de interes en la imagen
img_salida = cv.drawKeypoints(img_bnw, kp, None, (255,0,0), cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

# Mostramos la imagen con los puntos de interes
cv.namedWindow("ajedrez", cv.WINDOW_NORMAL)
cv.imshow("ajedrez", img_salida)
cv.waitKey()
cv.destroyAllWindows()
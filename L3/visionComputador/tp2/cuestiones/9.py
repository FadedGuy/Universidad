# Abrir y mostrar imagenes en color
# Mostrar cada uno de los canales BGR
# Transformar una imagen de niveles de gris y mostrar
# Desde BGR pasar a HSV. Mostrar cada uno de los canales HSV

import cv2 as cv

# Abrir imagen en color
img = cv.imread('img.jpg', 1)
if img is None:
    print("Unable to load image")
    exit()

# Transfomar imagen a solo un canal BGR
b = img.copy()
b[:,:,1]=0
b[:,:,2]=0

g = img.copy()
g[:,:,0]=0
g[:,:,2]=0

r = img.copy()
r[:,:,0]=0
r[:,:,1]=0

# Mostrar cada uno de los canales BGR
cv.namedWindow("img B", cv.WINDOW_NORMAL)
cv.namedWindow("img G", cv.WINDOW_NORMAL)
cv.namedWindow("img R", cv.WINDOW_NORMAL)
cv.imshow("img B", b)
cv.imshow("img G", g)
cv.imshow("img R", r)

#Transformar imagen a niveles de gris y mostrar
imgBNW = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.namedWindow("img bnw", cv.WINDOW_NORMAL)
cv.imshow("img bnw", imgBNW)

#Pasar de BGR a HSV
imgHSV = cv.cvtColor(img, cv.COLOR_BGR2HSV)

#Transformar para mostrar cada uno de los canales HSV
h = imgHSV.copy()
h[:,:,1]=0
h[:,:,2]=0

s = imgHSV.copy()
s[:,:,0]=0
s[:,:,2]=0

v = imgHSV.copy()
v[:,:,0]=0
v[:,:,1]=0

#Mostrar cada canales de HSV de la imagen transformada
cv.namedWindow("img h", cv.WINDOW_NORMAL)
cv.namedWindow("img s", cv.WINDOW_NORMAL)
cv.namedWindow("img v", cv.WINDOW_NORMAL)
cv.imshow("img h", h)
cv.imshow("img s", s)
cv.imshow("img v", v)

cv.waitKey(0)
cv.destroyAllWindows()

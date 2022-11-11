#Detección de patrones

import cv2
import numpy as np
from matplotlib import pyplot as plt

#Cargamos y hacemos una copia
imagen = cv2.imread('Grapadora.jpg', 1)
imagen2=cv2.cvtColor(imagen,cv2.COLOR_BGR2GRAY)
show_img = np.copy(imagen2)

print("trazar una línea sobre la imagen y pulsar ESC")

#Variables para el control del ratón que seleccionará el ROI
mouse_pressed = False
y = x = 0
y2 = x2 = 0

#Recorte con el ratón
def Dibujar_Linea(event, _x, _y, flags, param):
    global show_img, x, y, x2, y2, mouse_pressed
    if event == cv2.EVENT_LBUTTONDOWN:
        mouse_pressed = True
        x, y = _x, _y
        show_img = np.copy(imagen)
    elif event == cv2.EVENT_MOUSEMOVE:
        if mouse_pressed:
            show_img = np.copy(imagen)
            cv2.line(show_img, (x, y),(_x, _y), (255, 255, 255), 2)
    elif event == cv2.EVENT_LBUTTONUP:
        x2, y2 = _x, _y
        mouse_pressed = False

#Visualizamos la imagen        
cv2.namedWindow('image', cv2.WINDOW_NORMAL)
cv2.setMouseCallback('image', Dibujar_Linea)
while True:
    cv2.imshow('image', show_img)
    k = cv2.waitKey(1)
    if k == 27 and not mouse_pressed: #Pulsar esc cuando hemos terminado de dibujar
        break #tomamos la línea, confirmamos y cerramos.
cv2.destroyAllWindows()

if ((x2-x)==0):
    pendiente=1
    puntosY=np.arange(y, y2+1)
    puntosX=np.ones(puntosY.shape,np.int16)
    puntosX=x*puntosX
else:
    pendiente=(y2-y)/(x2-x)
    if ((x2-x)>(y2-y)):
        puntosX=np.arange(x, x2+1)
        puntosY=np.zeros(puntosX.shape,np.int16)
        puntosY=np.round(y+pendiente*(puntosX-x))
        puntosY=puntosY.astype(np.int16)
    else:
        puntosY=np.arange(y, y2+1)
        puntosX=np.zeros(puntosY.shape,np.int16)
        puntosX=np.round(x+(puntosY-y)/pendiente)
        puntosX=puntosX.astype(np.int16)

perfil=imagen2[puntosY,puntosX]

plt.plot(perfil),plt.title('Intensidad del perfil')
plt.show()




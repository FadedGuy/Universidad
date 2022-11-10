import cv2 as cv
import numpy as np
import utilidad as ut

# Funcion usada al utilizar el mouse en las ventanas
def mouseHandler(event, x, y, flags, param):
    if event == cv.EVENT_LBUTTONDBLCLK:
        if param == "original":
            global original_mouse

            if len(original_mouse) < 3:
                original_mouse.append([x, y])
            else: 
                print("Los puntos de esta ventana ya han sido capturados")
        elif param == "modif":
            global modif_mouse

            if len(modif_mouse) < 3:
                modif_mouse.append([x, y])
            else:
                print("Los puntos de esta ventana ya han sido capturados")
                            

img_original = cv.imread("Lenna.png")

# Escalado, translacion y rotacion de una imagen
img_modif = cv.resize(img_original, ut.calc_dsize(img_original, 1.25))

M_desp = ut.calc_m_desp(-52, 200)
M_rot = ut.calc_m_rot(57, 1, img_modif.shape[1]/2, img_modif.shape[0]/2)

img_modif = cv.warpAffine(img_modif, M_desp, ut.calc_dsize(img_modif))
img_modif = cv.warpAffine(img_modif, M_rot, ut.calc_dsize(img_modif))

# Mostramos las dos imagenes ademas de agregarles el callback a mi funcion mouseHandler
cv.namedWindow("Original", cv.WINDOW_AUTOSIZE)
cv.setMouseCallback("Original", mouseHandler, "original")
cv.imshow("Original", img_original)

cv.namedWindow("Modificada", cv.WINDOW_AUTOSIZE)
cv.setMouseCallback("Modificada", mouseHandler, "modif")
cv.imshow("Modificada", img_modif)

# Vectores utilizados para llevar los puntos seleccionados
original_mouse = []
modif_mouse = []

# Seleccionamos los 3 puntos de cada imagen y esperamos hasta que eso pase
print("Selecccionar los tres puntos coincidentes de la imagen original y modificada dando doble clic")
while len(original_mouse) < 3 or len(modif_mouse) < 3:
    key = cv.waitKey(1)&0xFF
    if key == ord('q'):
        break

print("Puntos seleccionados")

# Hacemos la conversion de regreso a partir de los puntos seleccionados
original = np.float32(original_mouse)
modif = np.float32(modif_mouse)

M_calculada = cv.getAffineTransform(modif, original)
img_calculada = cv.warpAffine(img_modif, M_calculada, ut.calc_dsize(img_modif))

# Mostramos la imagen con la matriz aplicada en base al calculo que se hizo, deberia de asemejarse a la imagen original
cv.imshow("Calculada", img_calculada)
cv.waitKey(0)

cv.destroyAllWindows()

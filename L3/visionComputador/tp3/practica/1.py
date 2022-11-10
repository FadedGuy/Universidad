# Cargar y mostrar una imagen.
# Modificar su tamaño 3 veces, menor a la original, mayor con vecino mas proximo, mayor con interpolacion bicubica
# Mostrarlas sin usar namedWindow y WINDOW_NORMAL.

import cv2 as cv
import utilidad as ut

# Cargamos una imagen
img_original = cv.imread("marilyn.jpg")

# Menor tamaño (la mitad para ser exactos)
d_size = ut.calc_dsize(img_original, 0.5)
img_menor = cv.resize(img_original, d_size)

# Mayor con vecino mas proximo
d_size = ut.calc_dsize(img_original, 3)
img_vecino = cv.resize(img_original, d_size, interpolation=cv.INTER_NEAREST)

# Mayor con bicubica
d_size = ut.calc_dsize(img_original, 3)
img_bicubica = cv.resize(img_original, d_size, interpolation=cv.INTER_CUBIC)

# Mostramos las imagenes
cv.imshow("Original", img_original)
cv.imshow("Primera", img_menor)
cv.imshow("Vecino", img_vecino)
cv.imshow("Bicubica", img_bicubica)

cv.waitKey(0) & 0xFF
cv.destroyAllWindows()
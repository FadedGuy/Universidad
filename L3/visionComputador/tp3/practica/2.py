# Crear una matriz de translacion, aplicarla a la imagen y mostrarla
# Crear una matriz de rotacion, aplicarla a la imagen y mostrarla

import cv2 as cv
import utilidad as ut

img_original = cv.imread("Lenna.png")

# Llamamos a la funcion calc_m_desp para obtener la matriz de translacion y calc_dsize para indicar el tamaño de la imagen de salida
img_desp = cv.warpAffine(img_original, ut.calc_m_desp(50, 15), ut.calc_dsize(img_original))

# Llamamos a la funcion calc_m_desp para obtener la matriz de translacion y calc_dsize para indicar el tamaño de la imagen de salida
img_rot = cv.warpAffine(img_original, ut.calc_m_rot(10, 1, img_original.shape[1]/2, img_original.shape[0]/2), ut.calc_dsize(img_original))

cv.imshow("Original", img_original)
cv.imshow("Desplazada", img_desp)
cv.imshow("Rotada", img_rot)

cv.waitKey(0) & 0xFF
cv.destroyAllWindows()
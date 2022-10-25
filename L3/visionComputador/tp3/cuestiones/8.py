# Usando team3 ayuda
import cv2 as cv
import numpy as np
import Ruido

img_original = cv.imread("rice.png", 0)

img_ruido = Ruido.SalyPimienta(img_original)

img_FT = np.fft.fft2(img_ruido) # Transformada de Fourier
img_FTCentro = np.fft.fftshift(img_FT) # Centrada

mag_1 = np.log(np.abs(img_FT) + 0.001)
img_mag_1 = mag_1 / mag_1.max()

mag_2 = np.log(np.abs(img_FTCentro) + 0.001)
img_mag_2 = mag_2 / mag_2.max()


cv.namedWindow("Imagen Original", cv.WINDOW_NORMAL)
cv.imshow("Imagen Original", img_original)

cv.namedWindow("Imagen FT", cv.WINDOW_NORMAL)
cv.imshow("Imagen FT", img_mag_1)

cv.namedWindow("Imagen FT Centrada", cv.WINDOW_NORMAL)
cv.imshow("Imagen FT Centrada", img_mag_2)

# Creamos una matriz de 0 en relacion al tama;o de la transformada de fourier centrada
mask = np.zeros(img_FTCentro.shape)
size = 30

mask[mask.shape[0]//2-size:mask.shape[0]//2+size,mask.shape[1]//2-size:mask.shape[1]//2+size] = 1

img_FTCentro=img_FTCentro*mask

img_centrada = np.fft.ifftshift(img_FTCentro)
img_final = np.fft.ifft2(img_centrada)

mag_1 = np.log(np.abs(img_centrada) + 0.001)
img_mag_1 = mag_1 / mag_1.max()

mag_2 = np.log(np.abs(img_final) + 0.001)
img_mag_2 = mag_2 / mag_2.max()


cv.namedWindow("Imagen FT Centrada Filtrada BG", cv.WINDOW_NORMAL)
cv.imshow("Imagen FT Centrada Filtrada BG", img_mag_1)

cv.namedWindow("Imagen Final", cv.WINDOW_NORMAL)
cv.imshow("Imagen Final", img_mag_2)

cv.waitKey(0)
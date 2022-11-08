# Cargar una imagen
# Diseñar un filtro paso bajo cuadrado para el caso de la fft centrada y aplicarselo
# Mostrar la imagen filtrada a partir de la fft inversa. Mostrar tanto antes como despues de aplicar el filtro

import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import Ruido

def filtro_pasobajo(img):
    row, col = img.shape
    mask = np.zeros(img.shape)
    size = 25
    
    mask[row//2-size:row//2+size, col//2-size:col//2+size] = 1
    img_ = img*mask
    return img_

# Cargamos la imagen en blanco y negro
img_original = cv.imread("img.jpg", 0)

img_ruido = Ruido.SalyPimienta(img_original)

# Obtenemos la fft centrada
img_FT = np.fft.fft2(img_ruido) # Transformada de Fourier
img_FTCentro = np.fft.fftshift(img_FT) # Centrada

mag_1 = np.log(np.abs(img_FTCentro) + 0.001)
mag_1 = mag_1 / mag_1.max()

# Aplicamos filtro paso bajo
img_pb = filtro_pasobajo(img_FTCentro)

# Realizamos la fft inversa 
img_centrada = np.fft.ifftshift(img_pb)
img_final = np.fft.ifft2(img_centrada)

mag_2 = np.log(np.abs(img_final) + 0.001)
mag_2 = mag_2 / mag_2.max()

# Mostramos la imagen original y final. Ademas de la fft antes y despues
cv.namedWindow("Original", cv.WINDOW_NORMAL)
cv.imshow("Original", img_original)

cv.namedWindow("Final", cv.WINDOW_NORMAL)
cv.imshow("Final", mag_2)

cv.waitKey(0)
cv.destroyAllWindows()

plt.title("FFT Centrada Antes")
plt.imshow(mag_1)
plt.show()


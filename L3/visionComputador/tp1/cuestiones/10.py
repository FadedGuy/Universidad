# Cargar una imagen
# Obtener su transformada de Fourir  y la transformada de Fourier centrada
# Visualizar su valor absoluto en escala logaritmica
import cv2 as cv
import numpy as np

img = cv.imread('Ventana.jpg',0)
if img is None:
    print("No se pudo abrir la imagen")
    exit()

# Obtenemos la transformada de Fourier y la transformada centrada
# En caso que necesitemos normalizar las imagenes
# _imgNorm = img / np.max(img) # Reales
# _imgNorm = 255*img/ np.max(img) # Enteros
img_FT = np.fft.fft2(img, norm="forward") # Transformada de Fourier
img_FTCentro = np.fft.fftshift(img_FT) # Centrada

# Visualizar su valor abosluto en escala logaritmica
# En valor absoluto ya que los numeros son complejos y en escala logaritmica ya que las
# variaciones son peques
mag_1 = np.log(np.abs(img_FT) + 0.00001)
mag_2 = np.log(np.abs(img_FTCentro) + 0.00001)

cv.namedWindow("Fourier", cv.WINDOW_NORMAL)
cv.namedWindow("Fouri2er", cv.WINDOW_NORMAL)
cv.imshow("Fourier", mag_1)
cv.imshow("Fouri2er", mag_2)
cv.waitKey(0)
cv.destroyAllWindows()
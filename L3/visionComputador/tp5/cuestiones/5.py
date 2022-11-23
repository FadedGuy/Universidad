import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
from MiLib import CalculoLBP

img_original_1 = cv.imread("imgs/Textura1.jpg", 0)
img_original_2 = cv.imread("imgs/Textura2.jpg", 0)
img_original_3 = cv.imread("imgs/Textura3.jpg", 0)

hist_1 = cv.calcHist([img_original_1], [0], None, [256], [0,256])
hist_2 = cv.calcHist([img_original_2], [0], None, [256], [0,256])
hist_3 = cv.calcHist([img_original_3], [0], None, [256], [0,256])

fft_1 = np.fft.fft2(img_original_1)
fft_2 = np.fft.fft2(img_original_2)
fft_3 = np.fft.fft2(img_original_3)

img_fft_1 = np.log(np.abs(fft_1) + 0.001)
img_fft_1 = img_fft_1 / img_fft_1.max()
img_fft_2 = np.log(np.abs(fft_2) + 0.001)
img_fft_2 = img_fft_2 / img_fft_2.max()
img_fft_3 = np.log(np.abs(fft_3) + 0.001)
img_fft_3 = img_fft_3 / img_fft_3.max()

lbp_1 = CalculoLBP(img_original_1)
lbp_2 = CalculoLBP(img_original_2)
lbp_3 = CalculoLBP(img_original_3)

print(cv.compareHist(lbp_1, lbp_1, cv.HISTCMP_CHISQR_ALT))
print(cv.compareHist(lbp_1, lbp_2, cv.HISTCMP_CHISQR_ALT))
print(cv.compareHist(lbp_1, lbp_3, cv.HISTCMP_CHISQR_ALT))

columna = 3
fila = 4
fig = plt.figure(figsize=(fila, columna))

fig.add_subplot(fila, columna, 1)
plt.imshow(img_original_1, cmap='gray')
fig.add_subplot(fila, columna, 2)
plt.imshow(img_original_2, cmap='gray')
fig.add_subplot(fila, columna, 3)
plt.imshow(img_original_3, cmap='gray')

fig.add_subplot(fila, columna, 4)
plt.plot(hist_1)
fig.add_subplot(fila, columna, 5)
plt.plot(hist_2)
fig.add_subplot(fila, columna, 6)
plt.plot(hist_3)

fig.add_subplot(fila, columna, 7)
plt.imshow(img_fft_1, cmap='gray')
fig.add_subplot(fila, columna, 8)
plt.imshow(img_fft_2, cmap='gray')
fig.add_subplot(fila, columna, 9)
plt.imshow(img_fft_3, cmap='gray')

fig.add_subplot(fila, columna, 10)
plt.plot(lbp_1)
fig.add_subplot(fila, columna, 11)
plt.plot(lbp_2)
fig.add_subplot(fila, columna, 12)
plt.plot(lbp_3)

plt.show()

# cv.namedWindow("Original 1", cv.WINDOW_NORMAL)
# cv.namedWindow("Original 2", cv.WINDOW_NORMAL)
# cv.namedWindow("Original 3", cv.WINDOW_NORMAL)
# cv.imshow("Original 1", img_original_1)
# cv.imshow("Original 2", img_original_2)
# cv.imshow("Original 3", img_original_3)
# cv.waitKey()

# DUDA
import matplotlib.pyplot as plt
import cv2 as cv

img = cv.imread("ching1.png", 0)
plt.hist(img.ravel(), 256, [0, 256])
plt.show()
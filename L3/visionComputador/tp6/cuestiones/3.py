import cv2 as cv
import numpy as np

def expandHist(img, gamma, p1 = 0, p2 = 255):
    aux = np.maximum(img, p1)
    aux2 = np.minimum(aux, p2)

    sub = np.subtract(aux2, p1)
    img2 = np.true_divide(sub, (p2-p1))

    img3 = np.power(img2, gamma)

    return img3

# Cargamos ambas imagenes
img_original_1 = cv.imread("imgs/aula1.jpg")
img_original_2 = cv.imread("imgs/aula2.jpg")

# Eliminamos ruido y mejoramos contraste
img_1 = expandHist(img_original_1, 1.7)
img_2 = expandHist(img_original_2, 1.7)

img_1 = cv.GaussianBlur(img_1, (3,3), 3)
img_2 = cv.GaussianBlur(img_2, (3,3), 3)

img_1 = cv.normalize(img_1, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)
img_2 = cv.normalize(img_2, None, 255, 0, cv.NORM_MINMAX, cv.CV_8UC1)

# Creamos un objeto BRISK y describimos los puntos de interes de las imagenes
brisk = cv.BRISK_create(125, 5)
kp1, des1 = brisk.detectAndCompute(img_1, None)
kp2, des2 = brisk.detectAndCompute(img_2, None)

# Llamamos un Brute-Force Matcher para emparejas los puntos 
bf_matcher = cv.BFMatcher(cv.NORM_L2, True)
# bf_matcher = cv.BFMatcher(cv.NORM_HAMMING, True)
parejas = bf_matcher.match(des1, des2)
parejas = sorted(parejas, key=lambda x:x.distance)

# Dibujamos aquellos puntos que fueron emparejados, la flag indica que dibujaremos solamente aquellos
# que fueron emparejados, no los keypoints
img_parejas = np.zeros((1,1))
img_parejas = cv.drawMatches(img_1, kp1, img_2, kp2, parejas[:20], img_parejas, flags=cv.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

cv.namedWindow("img 1", cv.WINDOW_NORMAL)
cv.namedWindow("img 2", cv.WINDOW_NORMAL)
cv.namedWindow("img parejas", cv.WINDOW_NORMAL)
cv.imshow("img 1", img_1)
cv.imshow("img 2", img_2)
cv.imshow("img parejas", img_parejas)

cv.waitKey()
cv.destroyAllWindows()
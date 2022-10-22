import cv2 as cv

img = cv.imread('img.jpg')
if img is None:
    print("Unable to load image")
    exit()

imagenHSV = cv.cvtColor(img, cv.COLOR_BGR2HSV)
cv.namedWindow("img hsv", cv.WINDOW_NORMAL)
cv.imshow("img hsv", imagenHSV)

cv.waitKey(0)
cv.destroyAllWindows()

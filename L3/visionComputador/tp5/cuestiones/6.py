import cv2 as cv

img_original = cv.imread("imgs/Herramientas.JPG")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

img_bnw = cv.medianBlur(img_bnw, 3)
retval, img_binary = cv.threshold(img_bnw, 80, 256, cv.THRESH_BINARY_INV | cv.THRESH_OTSU)
kernel = cv.getStructuringElement(cv.MORPH_RECT, (10,10))
img_binary = cv.dilate(img_binary, kernel)

countours, hierarchy = cv.findContours(img_binary, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)

huMoments = list()
for countour in countours:
    huMoments.append(cv.HuMoments(cv.moments(countour)))

print(huMoments[0])
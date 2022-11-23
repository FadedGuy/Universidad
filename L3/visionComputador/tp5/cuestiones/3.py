import cv2 as cv

img_original = cv.imread("imgs/formas.JPG")

img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)
img_envolturas = img_bnw.copy()

retval, img_binary = cv.threshold(img_bnw, 150, 255, cv.THRESH_BINARY_INV)
countours, hierarchy = cv.findContours(img_binary, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)

cv.drawContours(img_original, countours, -1, 0, 3)

contourList = list()
for i in range(len(countours)):
    contourDict = {"id": "0", "area": "0", "perimetro": "0", "orientacion": "0", "solidez": "0", "elongacion" : "0"}

    area = cv.contourArea(countours[i])
    perimetro = cv.arcLength(countours[i], True)
    (xx, yy), (MA, ma), angle = cv.fitEllipse(countours[i])
    elongacion = MA/ma

    envolturas = cv.convexHull(countours[i])
    solidez = area / cv.contourArea(envolturas)

    contourDict.update({"id": i})
    contourDict.update({"area": area})
    contourDict.update({"perimetro": perimetro})
    contourDict.update({"solidez": solidez})
    contourDict.update({"orientacion": angle})
    contourDict.update({"elongacion": elongacion})

    contourList.append(contourDict)

    cv.putText(img_original, str(i), (countours[i][0][0][0], countours[i][0][0][1]), cv.FONT_HERSHEY_PLAIN, 2, (0, 0, 0), 3, cv.LINE_4)
    cv.polylines(img_envolturas, [envolturas], True, (0, 0, 0), 2)


cv.imshow("original", img_original)
cv.imshow("envolturas", img_envolturas)
cv.waitKey()
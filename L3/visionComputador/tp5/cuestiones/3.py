import cv2 as cv

# Cargamos la imagen y la transformamos en blanco y negro
img_original = cv.imread("imgs/formas.JPG")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

# Mantenemos dos copias de la imagen sobre la cual dibujaremos los la envoltura y contornos
img_contours = img_original.copy()
img_envolturas = img_original.copy()

# Binarizamos la imagen
retval, img_binary = cv.threshold(img_bnw, 150, 255, cv.THRESH_BINARY_INV)

# Obtenemos los contornos externos de la imagen binarizada y los dibujamos sobre la imagen original
countours, hierarchy = cv.findContours(img_binary, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)
cv.drawContours(img_contours, countours, -1, 0, 3)

contourList = list()
for i in range(len(countours)):
    # Diccionario donde mantendremos las propiedades del objeto
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

    # Numeramos los contornos y dibujamos las envolturas
    cv.putText(img_contours, str(i), (countours[i][0][0][0], countours[i][0][0][1]), cv.FONT_HERSHEY_PLAIN, 2, (0, 0, 0), 3, cv.LINE_4)
    cv.polylines(img_envolturas, [envolturas], True, (0, 0, 0), 2)


# Mostramos la imagen original, la imagen binaria, la imagen con contornos y numero y la imagen con las envolturas convexas
cv.imshow("original", img_original)
cv.imshow("binaria", img_binary)
cv.imshow("contornos", img_contours)
cv.imshow("envolturas", img_envolturas)
cv.waitKey()
cv.destroyAllWindows()
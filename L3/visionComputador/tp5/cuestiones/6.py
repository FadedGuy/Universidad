import cv2 as cv

# Cargamos una de las imagenes resultados del ejercicio 4
img_original = cv.imread("imgs/resultado4.png")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)

# Guardamos los contornos externos del objeto
countours, hierarchy = cv.findContours(img_bnw, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)

# Recorremos los contornos
huMoments = list()
for countour in countours:
    # Agregamos los momentos a la lista
    huMoments.append(cv.HuMoments(cv.moments(countour)))

# Imprimir los momentos
print(huMoments[0])
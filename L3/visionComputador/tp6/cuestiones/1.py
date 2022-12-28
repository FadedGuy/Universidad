import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

# Obtenemos los contornos y guardamos su boundingRect
# Estan ordenadas por orden de salida, no por el numero siendo aquel que indica el nombre del archivo
def guardar_contornos_externos(img):
    contours, hierarchy = cv.findContours(img, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)

    cnt = 0
    for i in range(len(contours)):
        if(hierarchy[0][i][3] == -1):
            x, y, w, h =  cv.boundingRect(contours[i])
            obj = img[y: y+h, x:x+w]
            cv.imwrite(f"imgs/num_{cnt}.jpg", obj)
            cnt+=1
    
    return cnt

# Comparacion de patron con el numero i
def comparacion_template(img_original, img_numero, img_patron):
    img_prueba = np.zeros(img_original.shape, np.uint8)

    fil, col, _ = img_numero.shape
    img_prueba[0:fil, 0:col] = img_numero

    salida = cv.matchTemplate(img_prueba, img_patron, cv.TM_CCOEFF_NORMED)

    # Regresamos el maximo de las correlaciones cruzadas 
    return np.max(salida)


# Abrimos y binarizamos la imagen
img_original = cv.imread("imgs/numeros.jpg")
img_bnw = cv.cvtColor(img_original, cv.COLOR_BGR2GRAY)
retval, img_binary = cv.threshold(img_bnw, 150, 255, cv.THRESH_BINARY_INV)

cnt = guardar_contornos_externos(img_binary)

# Imagen que sera el patron con el cual comparar el resto
num_i = 2
img_patron = cv.imread(f"imgs/num_{num_i}.jpg")


for i in range(cnt):
    img_num = cv.imread(f"imgs/num_{i}.jpg")
    max = comparacion_template(img_original, img_num, img_patron)

    # Indicamos aquel que es la misma imagen al patron, por lo cual su correlacion cruzada sera 1.0
    # la maxima en similitud
    if i == num_i:
        print("Here:")
    print(max)

cv.waitKey()
cv.destroyAllWindows()
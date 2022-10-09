# Cargar dos imagenes
# addWeighted de ambas imagenes 
# substract de ambas imagenes
# Es lo mismo restar chin1 - chin2 que chin2 - chin1? Cual es la diferencia
# Para que serviria realizar la resta de dos imagenes como las del ejemplo
import cv2 as cv

chin1 = cv.imread("chin1.jpeg")
if chin1 is None:
    print("Unable to load chin1")
    exit()

chin2 = cv.imread("chin2.jpeg")
if chin2 is None:
    print("Unable to load chin2")
    exit()

alpha = 0.5
beta = 1 - alpha

# addWeighted
dst_add_12 = cv.addWeighted(chin1, alpha, chin2, beta, 0.0)
dst_add_21 = cv.addWeighted(chin2, alpha, chin1, beta, 0.0)

# Hacemos que la imagen se rescale a lo que quepa en pantalla y no se desborde
cv.namedWindow("added weight 12", cv.WINDOW_NORMAL)
cv.namedWindow("added weight 12", cv.WINDOW_NORMAL)
cv.imshow("added weight 12", dst_add_12)
cv.imshow("added weight 21", dst_add_21)
cv.waitKey(0)
# Para addWeighted no hay una diferencia entre poner una delante de la otra

# substract
# El 0 que aparece como parametro al final es el dtype, lo que significa, la profundidad que tendra
# la matriz de salida
dst_res_12 = cv.subtract(chin1, chin2, 0)
dst_res_21 = cv.subtract(chin2, chin1, 0)

cv.namedWindow("sub weight 12", cv.WINDOW_NORMAL)
cv.namedWindow("sub weight 21", cv.WINDOW_NORMAL)
cv.imshow("sub weight 12", dst_res_12)
cv.imshow("sub weight 21", dst_res_21)
# No es lo mismo, lo que se nota es que la que vaya primero va a estar por encima de la otra
# Podria servir para superponer una imagen sobre otra y detectar cambios de una imagen a otra 
# que pueden ser continuas o desde el mismo angulo

cv.waitKey(0)
cv.destroyAllWindows()

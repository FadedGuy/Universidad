# Cargar dos imagenes
# addWeighted de ambas imagenes 
# substract de ambas imagenes
# Es lo mismo restar chin1 - chin2 que chin2 - chin1? Cual es la diferencia
# Para que serviria realizar la resta de dos imagenes como las del ejemplo
import cv2 as cv

# O en png son imagenes distintas
chin1 = cv.imread("chin1.jpeg")
if chin1 is None:
    print("Unable to load chin1")
    exit()

chin2 = cv.imread("chin2.jpeg")
if chin2 is None:
    print("Unable to load chin2")
    exit()

chin1 = cv.resize(chin1, (700, 931))
chin2 = cv.resize(chin2, (700, 931))

alpha = 0.5
beta = 1 - alpha

# addWeighted
dst_add_12 = cv.addWeighted(chin1, alpha, chin2, beta, 0.0)
dst_add_21 = cv.addWeighted(chin2, alpha, chin1, beta, 0.0)

cv.imshow("added weight 12", dst_add_12)
cv.imshow("added weight 21", dst_add_21)
cv.waitKey(0)
# Para addWeighted no hay una diferencia entre poner una delante de la otra

# substract
dst_res_12 = cv.subtract(chin1, chin2, 0)
dst_res_21 = cv.subtract(chin2, chin1, 0)

cv.imshow("sub weight 12", dst_res_12)
cv.imshow("sub weight 21", dst_res_21)
# No es lo mismo, lo que se nota es que la que vaya primero va a estar por encima de la otra
# Podria servir para superponer una imagen sobre otra y detectar cambios de una imagen a otra 
# que pueden ser continuas o el mismo angulo
# El 0 que aparece como parametro al final es el dtype, lo que significa, la profundidad que tendra
# la matriz de salida

cv.waitKey(0)
cv.destroyAllWindows()

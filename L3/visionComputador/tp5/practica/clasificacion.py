import cv2 as cv
import json
from enum import Enum
from mediciones import procesar

# Nombre del archivo con las medidas de las clases
ARCHIVO_MEDIDAS = "Medidas.json"
# Cantidad de veces que la funcion discriminante ajustara su tolerancia
MAX_STEPS = 5
# Modificacion por paso de la tolerancia
STEPS_TOLERANCIA = 0.05


class Imagenes(Enum):
    ALL1 = "ALL1.jpg"
    ALL2 = "ALL2.jpg"
    GOMA1 = "GOMA1.jpg"
    GOMA2 = "GOMA2.jpg"
    LAPIZ1 = "LAPIZ1.jpg"
    LAPIZ2 = "LAPIZ2.jpg"
    ROT1 = "ROT1.jpg"
    ROT2 = "ROT2.jpg"


# Usando json obtenemos los datos del archivo
def obtener_medidas_discriminantes(filename):
    data = ""
    with open(filename, "r") as f:
        try:
            data = json.load(f)
        except json.JSONDecodeError:
            return None

    return data


# Nos regresa las medidas que usamos para la clasificacion asi como el punto donde poner el texto de su clase
def obtener_medidas_objetos(obj_bnw):
    obj_bnw = cv.cvtColor(obj, cv.COLOR_BGR2GRAY)

    countours, hierarchy = cv.findContours(obj_bnw, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)
    # En algunos casos el primer contorno no es el correcto, es el segundo (ALL1.jpg)
    try:
        (xx, yy), (MA, ma), angle = cv.fitEllipse(countours[0])
    except cv.error:
        (xx, yy), (MA, ma), angle = cv.fitEllipse(countours[1])

    elongacion = MA/ma
    huMoments = cv.HuMoments(cv.moments(countours[0]))

    return [elongacion, huMoments], countours[0][0]


def funcion_discriminante(elongacion, hu, data, tolerancia, steps=0):
    clase_obj = ""
    # Iteramos por las clases e intentamos ver si es la clase correspondiente al objeto que tenemos
    for clase in data:
        elongacion_clase, dev_elongacion_clase = float(clase['elongacion']), float(clase['devElongacion'])
        hu_clase, dev_hu_clase = float(clase['hu']), float(clase['devHu'])

        if elongacion - (dev_elongacion_clase * tolerancia) <= elongacion_clase and elongacion + (dev_elongacion_clase* tolerancia) >= elongacion_clase\
         or hu - (dev_hu_clase * tolerancia) <= hu_clase and hu + (dev_hu_clase* tolerancia) >= hu_clase:
            clase_obj = clase['id']
            break
    
    # En caso que no se haya encontrado objeto ajustamos la tolerancia
    if clase_obj == "" and steps < MAX_STEPS:
        return funcion_discriminante(elongacion, hu, data, tolerancia+STEPS_TOLERANCIA, steps+1)
    if clase_obj == "" and steps == MAX_STEPS:
        print("Steps maximos alcanzadas para relacionar objeto con objetos conocidos")
    
    return clase_obj


def clasificador(obj, data, tolerancia = 1.2):
    data_obj, punto_clave = obtener_medidas_objetos(obj)

    elongacion, hu = data_obj[0], data_obj[1]
    clase_obj = funcion_discriminante(elongacion, hu[0], data, tolerancia)

    return [clase_obj, punto_clave]


if __name__ == "__main__":
    data = obtener_medidas_discriminantes(ARCHIVO_MEDIDAS)
    # Usamos la misma funcion de obtencion de etiquetas que para la obtencion de mediciones
    # img_original, img_tag, tag_imgs = procesar(f"imgs/{Imagenes.ALL1.value}")
    img_original, img_tag, tag_imgs = procesar(f"imgs/{Imagenes.ALL2.value}")

    # Generamos una copia de la imagen original sobre la cual pondremos el texto de las clases de los objetos
    img_cpy = img_original.copy()
    for obj in tag_imgs:
        clasificacion, punto_clave = clasificador(obj, data)
        cv.putText(img_cpy, clasificacion, (punto_clave[0][0], punto_clave[0][1]), cv.FONT_HERSHEY_PLAIN, 15, 250, 15, cv.LINE_4)

    cv.namedWindow("Etiquetada", cv.WINDOW_NORMAL)
    cv.imshow("Etiquetada", img_cpy)

    cv.waitKey()
    cv.destroyAllWindows()
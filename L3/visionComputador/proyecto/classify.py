import cv2 as cv
from keras.models import load_model
import keras.utils as image
import matplotlib.pyplot as plt
import numpy as np
import os

from utils import *

# Funcion que predice continuamente uno de los objetos visible en la camara 
def predict_from_camera(model):
    # Obtenemos la camara del ordenador y checamos por errores
    camera = cv.VideoCapture(0)
    if not camera.isOpened():
        print('Error al abrir la camara')
        exit()

    # Variables usadas dentro del bucle para control de opciones
    alwaysOn = False
    capture = False
    prediccion_label = ""

    # Creamos la ventana donde se mostrara el feed de la camara 
    cv.namedWindow("Camara", cv.WINDOW_NORMAL)
    while True:
        capture = False

        # Leemos el frame actual de la camara y verificamos errores
        valid, frame = camera.read()
        if not valid:
            print("Error al recibir el siguiente frame")
            break
        
        # Escalamos el tamaño de frame al esperado por nuestro modelo
        frame = cv.resize(frame, INPUT_SIZE)

        # Opciones de control
        key = cv.waitKey(24)&0xFF
        if key == ord('q'):
            break
        if key == ord('a'):
            alwaysOn = not alwaysOn
        if key == ord('c'):
            capture = True

        if alwaysOn or capture:
            # Convertimos el frame a una imagen aceptada por el modelo
            frame_tensor = image.img_to_array(frame)
            frame_tensor = np.expand_dims(frame_tensor, axis=0)
            frame_tensor /= 255

            # Identificamos el objeto que se muestra en la camara 
            # usando la prediccion de nuestro modelo
            prediccion = model.predict(frame_tensor, batch_size=1, steps=1)
            print(prediccion)
            print(prediccion_label)

            # Solo mostraremos un resultado si nuestro nivel de confianza es suficientemente alto
            if np.max(prediccion) >= UMBRAL_PREDICCION:
                prediccion_label = class_labels[np.argmax(prediccion, axis=1)[0]]

        # Agrega nuestra prediccion al frame
        cv.putText(frame, prediccion_label, (15,30), cv.FONT_HERSHEY_PLAIN, 2, 150, 2, cv.LINE_4)

        # Se muestra el frame de la camara
        cv.imshow("Camara", frame)


    # Liberamos la camara y destruimos todas las ventanas
    camera.release()
    cv.destroyAllWindows()


# Funcion para uso en caso que no funcione la camara del ordenador
# o se busque ver el comportamiento ante ciertos detalles o patrones
def predict_from_file(model):
    dir_actual = os.getcwd() 
    dir_base = os.path.join(dir_actual, 'dataset')

    nombre = 'Lapiz_1.jpg'
    img_path = os.path.join(dir_base, nombre)
    img = image.load_img(img_path, target_size=INPUT_SIZE)
    img_tensor = image.img_to_array(img)
    img_tensor = np.expand_dims(img_tensor, axis=0)
    img_tensor /= 255

    predicciones = model.predict(img_tensor, batch_size=1, steps=1)
    print(predicciones)
    n_label = np.argmax(predicciones, axis=1)[0]
    print(n_label)

    plt.imshow(img_tensor[0])
    plt.title(class_labels[n_label])
    plt.axis('off')
    plt.show()


if __name__ == "__main__":
    # Cargamos el modelo entrenado 
    model = load_model(MODEL_FILENAME)
    
    predict_from_camera(model)
    # predict_from_file(model)
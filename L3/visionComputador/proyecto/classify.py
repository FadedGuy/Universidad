import cv2 as cv
from keras.models import load_model
import keras.utils as image
import numpy as np

from utils import *

# Cargamos el modelo entrenado 
model = load_model(MODEL_FILENAME)

# Obtenemos la camara del ordenador y checamos por errores
camera = cv.VideoCapture(0)
if not camera.isOpened():
    print('Error al abrir la camara')
    exit()

# Creamos la ventana donde se mostrara el feed de la camara 
cv.namedWindow("Camara", cv.WINDOW_NORMAL)
while True:
    # Leemos el frame actual de la camara y verificamos errores
    valid, frame = camera.read()
    if not valid:
        print("Error al recibir el siguiente frame")
        break

    # Adaptamos el frame a una imagen aceptada por el modelo
    frame = cv.resize(frame, INPUT_SIZE)
    frame_tensor = image.img_to_array(frame)
    frame_tensor = np.expand_dims(frame_tensor, axis=0)
    frame_tensor /= 255

    # Identificamos el objeto que se muestra en la camara 
    # usando la prediccion de nuestro modelo
    prediccion = model.predict(frame_tensor, batch_size=1, steps=1)
    prediccion_label = class_labels[np.argmax(prediccion, axis=1)[0]]
    print(prediccion_label)

    # Se muestra el frame de la camara
    cv.imshow("Camara", frame)
    key = cv.waitKey(24)&0xFF
    if key == ord('q'):
        break

# Liberamos la camara y destruimos todas las ventanas
camera.release()
cv.destroyAllWindows()


# model = load_model('model.h5')

# dir_actual = os.getcwd() 
# dir_base = os.path.join(dir_actual, 'dataset')

# nombre = 'Lapiz_1.jpg'
# img_path = os.path.join(dir_base, nombre)
# img = image.load_img(img_path, target_size=INPUT_SIZE)
# img_tensor = image.img_to_array(img)
# img_tensor = np.expand_dims(img_tensor, axis=0)
# img_tensor /= 255

# predicciones = model.predict(img_tensor, batch_size=1, steps=1)
# print(predicciones)
# n_label = np.argmax(predicciones, axis=1)[0]
# print(n_label)

# plt.imshow(img_tensor[0])
# plt.title(class_labels[n_label])
# plt.axis('off')
# plt.show()
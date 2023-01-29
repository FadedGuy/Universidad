from keras.models import load_model
import keras.utils as image
import os
import numpy as np
import matplotlib.pyplot as plt
from functions import *

import cv2 as cv

model = load_model(MODEL_FILENAME)

camera = cv.VideoCapture(0)
if not camera.isOpened():
    print('Error al abrir la camara')
    exit()

cv.namedWindow("Camara", cv.WINDOW_NORMAL)
while True:
    valid, frame = camera.read()

    if not valid:
        print("Error al recibir el siguiente frame")
        break

    frame_tensor = cv.resize(frame, INPUT_SIZE)
    frame_tensor = image.img_to_array(frame_tensor)
    frame_tensor = np.expand_dims(frame_tensor, axis=0)
    frame_tensor /= 255

    prediccion = model.predict(frame_tensor, batch_size=1, steps=1)
    print(np.argmax(prediccion, axis=1)[0])

    cv.imshow("Camara", frame)
    key = cv.waitKey(24)&0xFF
    if key == ord('q'):
        break

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
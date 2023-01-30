import errno
import os
import shutil

from keras import optimizers
from keras.applications import MobileNetV2
from keras.layers import Input, Dense, Flatten, MaxPooling2D, Dropout
from keras.models import Model
from keras.preprocessing.image import ImageDataGenerator
import matplotlib.pyplot as plt

from utils import *

import visualkeras

# Funcion que crea el directorio si no existe, en caso que el directorio
# exista, se borra y crea uno nuevo
def mkdir_custom(dir):
    try:
        os.mkdir(dir)
    except OSError as err:
        if err.errno != errno.EEXIST:
            raise
        
        shutil.rmtree(dir)
        os.mkdir(dir)


# Funcion que separa una clase de imagenes en test, validacion y entrenamiento
def separate_files(nombre, dir_base, dir_test, dir_train, dir_validate):
    # Entrenamiento
    fich_nombres = [nombre+str(i)+'.jpg' for i in range(1, TRAIN_RANGE)]
    copy_files_to_path(dir_base, dir_train, fich_nombres)

    # Validacion
    fich_nombres = [nombre+str(i)+'.jpg' for i in range(TRAIN_RANGE, VALIDATE_RANGE)]
    copy_files_to_path(dir_base, dir_validate, fich_nombres)

    # Test
    fich_nombres = [nombre+str(i)+'.jpg' for i in range(VALIDATE_RANGE, TEST_RANGE)]
    copy_files_to_path(dir_base, dir_test, fich_nombres)


# Funcion que copia los archivos indicados de un directorio a otro
def copy_files_to_path(dir_base, dir_destino, nombres):
    for nombre in nombres:
        origen = os.path.join(dir_base, nombre)
        destino = os.path.join(dir_destino, nombre)
        shutil.copyfile(origen, destino)


# Funcion que crea nuestro modelo, este se sobrepone a un modelo existente
# llamado MobileNetV2 y entrenado con el dataset de imagenet
def create_model():
    # Cargamos el modelo pre-entrenado de MobileNetV2 sin la ultima capa
    base_model = MobileNetV2(weights='imagenet', 
                             include_top=False, 
                             input_tensor=Input(shape=INPUT_SHAPE))

    # Creamos la capa de ingreso a nuestra parte de la red, esta debe ser de igual
    # talla al de MobileNetV2 especificado arriba
    head = base_model.output

    # Creamos las capas del final del modelo para ajustarlo a nuestras necesidades
    head = MaxPooling2D((2, 2))(head)
    head = Dropout(0.2)(head)
    head = Flatten()(head)
    # Uso 1000 ya que es la salida original que tiene el modelo MobileNetV2
    head = Dense(1000, activation='relu')(head)
    # La ultima capa muestra el numero de clases que deseamos detectar con 
    # un vector de la probabilidad de pertenecer a las distintas clases
    # La suma de todas las clases debe ser 1.0
    head = Dense(3, activation='softmax')(head)

    # Indicamos que no re-entrenaremos las capas del modelo ya entrenado (transfer learning)
    for layer in base_model.layers:
        layer.trainable = False

    # Juntamos los dos modelos, los compilamos e imprimimos su estructura
    model = Model(base_model.inputs, head)
    model.compile(loss='categorical_crossentropy', 
                  optimizer=optimizers.RMSprop(learning_rate=1e-5), 
                  metrics=['acc'])
    model.summary()

    # Muestra el modelo de una manera mas visual que el resumen en consola
    # requiere visualkeras instalable desde pip
    # visualkeras.layered_view(model, legend=True).show()    

    return model


# Funcion que grafica los resultados de entrenamiento y validacion
# de un modelo
def plot_results(history):
    acc = history.history['acc']
    val_acc = history.history['val_acc']
    loss = history.history['loss']
    val_loss = history.history['val_loss']
    epochs = range(1, len(acc) + 1)

    plt.plot(epochs, acc, 'bo', label='Training acc')    
    plt.plot(epochs, val_acc, 'b', label='Validation acc')    
    plt.title('Training and validation accuracy')
    plt.legend()
    plt.figure()
    plt.plot(epochs, loss, 'bo', label='Training loss')
    plt.plot(epochs, val_loss, 'b', label='Validation loss')
    plt.title('Perdidas de entrenamiento y validacion')
    plt.legend()
    plt.show()


# Funcion que ordena el dataset en las carpetas correspondientes
def setup(dir_base):
    # Creamos los 3 directorios que se usaran (train, validate, test)
    # con las respectivas clases dentro de cada uno (goma, rotulador, lapiz)
    dir_train = os.path.join(dir_base, 'train')
    mkdir_custom(dir_train)
    dir_validate = os.path.join(dir_base, 'validate')
    mkdir_custom(dir_validate)
    dir_test = os.path.join(dir_base, 'test')
    mkdir_custom(dir_test)

    dir_train_goma = os.path.join(dir_train, 'goma')
    mkdir_custom(dir_train_goma)
    dir_train_rotulador = os.path.join(dir_train, 'rotulador')
    mkdir_custom(dir_train_rotulador)
    dir_train_lapiz = os.path.join(dir_train, 'lapiz')
    mkdir_custom(dir_train_lapiz)

    dir_validate_goma = os.path.join(dir_validate, 'goma')
    mkdir_custom(dir_validate_goma)
    dir_validate_rotulador = os.path.join(dir_validate, 'rotulador')
    mkdir_custom(dir_validate_rotulador)
    dir_validate_lapiz = os.path.join(dir_validate, 'lapiz')
    mkdir_custom(dir_validate_lapiz)

    dir_test_goma = os.path.join(dir_test, 'goma')
    mkdir_custom(dir_test_goma)
    dir_test_rotulador = os.path.join(dir_test, 'rotulador')
    mkdir_custom(dir_test_rotulador)
    dir_test_lapiz = os.path.join(dir_test, 'lapiz')
    mkdir_custom(dir_test_lapiz)


    # Copiamos nuestro dataset a sus respectivas carpetas
    separate_files('Goma_', dir_base, dir_test_goma, dir_train_goma, dir_validate_goma)
    separate_files('Lapiz_', dir_base, dir_test_lapiz, dir_train_lapiz, dir_validate_lapiz)
    separate_files('Rotulador_', dir_base, dir_test_rotulador, dir_train_rotulador, dir_validate_rotulador)

    return dir_train


def main(dir_train):
    # Hacemos un preprocesado de las imagenes de entrenamiento y validacion (normalizacion a ambas)
    # Se escalan, y aplican diversas de transformacion para aumentar 
    # la diversidad de las imagenes de entrenamiento ya que nuestro dataset es poco
    train_datagen = ImageDataGenerator(rescale=1./255, rotation_range=40, width_shift_range=0.2, height_shift_range=0.2, shear_range=0.2, zoom_range=0.2, horizontal_flip=True)
    valid_datagen = ImageDataGenerator(rescale=1./255)
    train_generator = train_datagen.flow_from_directory(dir_train, target_size=INPUT_SIZE, batch_size=5, class_mode='categorical')
    validation_generator = valid_datagen.flow_from_directory(dir_train, target_size=INPUT_SIZE, batch_size=5, class_mode='categorical')
    
    # Creamos y entrenamos nuestro modelo con las imagenes de la etapa anterior 
    model = create_model()
    history = model.fit(train_generator, steps_per_epoch=5, epochs=12, validation_data=validation_generator, validation_steps=3)
    # Guardamos el modelo para utilizarlo a futuro sin volver a crear y entrenarlo
    model.save(MODEL_FILENAME)
    
    # Graficamos los resultados de perdida y precision el entrenamiento y validacion
    plot_results(history)


if __name__ == "__main__":
    dir_actual = os.getcwd() 
    dir_base = os.path.join(dir_actual, 'dataset')
    dir_train = os.path.join(dir_base, 'train')

    # Activar setup solo la primera vez que se corra el programa
    # dir_train = setup(dir_base)
    main(dir_train)

import os
import errno
import shutil

from keras import optimizers

from keras.applications import MobileNetV2
from keras.layers import Input
from keras.layers import Dense
from keras.layers import Flatten
from keras.layers import MaxPooling2D

from keras.models import Model
from keras.preprocessing.image import ImageDataGenerator

import matplotlib.pyplot as plt

from functions import *

# Funcion que usa mkdir de una manera segura, cuando encuentra que el directorio
# existe no pasa nada, pero cuando cualquier otra expcecion ocurre, se activa
# Cuando existe ya el fichero, se borra todo su interior y se crea uno nuevo
def mkdir_custom(dir):
    try:
        os.mkdir(dir)
    except OSError as err:
        if err.errno != errno.EEXIST:
            raise
        
        shutil.rmtree(dir)
        os.mkdir(dir)

def copy_files_to_path(dir_base, dir_destino, nombres):
    for nombre in nombres:
        origen = os.path.join(dir_base, nombre)
        destino = os.path.join(dir_destino, nombre)
        shutil.copyfile(origen, destino)

def create_model():
    base_model = MobileNetV2(weights='imagenet', include_top=False, input_tensor=Input(shape=INPUT_SHAPE))
    base_model.trainable = False
    inputs = Input(shape=INPUT_SHAPE)

    x = base_model(inputs, training=False)

    x = MaxPooling2D((2,2))(x)
    x = Flatten()(x)
    outputs = Dense(512, activation='relu')(x)
    outputs = Dense(3, activation='softmax')(x)
    model = Model(inputs, outputs)
    model.compile(loss='categorical_crossentropy', optimizer=optimizers.RMSprop(learning_rate=1e-4), metrics=['acc'])
    model.summary()


    return model

    # modelo_fin.compile(loss='categorical_crossentropy', optimizer=optimizers.RMSprop(learning_rate=1e-4), metrics=['acc'])
    # print(modelo_fin.summary())
    # return modelo_fin

def setup():
    # Crear directorios necesarios
    dir_actual = os.getcwd() 
    dir_base = os.path.join(dir_actual, 'dataset')

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


    # Ordenar el dataset en test/train/validate y goma/lapiz/rotulador
    # Goma
    fich_nombres = ['Goma_'+str(i)+'.jpg' for i in range(1, TRAIN_RANGE)]
    copy_files_to_path(dir_base, dir_train_goma, fich_nombres)
    fich_nombres = ['Goma_'+str(i)+'.jpg' for i in range(TRAIN_RANGE, VALIDATE_RANGE)]
    copy_files_to_path(dir_base, dir_validate_goma, fich_nombres)
    fich_nombres = ['Goma_'+str(i)+'.jpg' for i in range(VALIDATE_RANGE, TEST_RANGE)]
    copy_files_to_path(dir_base, dir_test_goma, fich_nombres)
    
    # Lapiz
    fich_nombres = ['Lapiz_'+str(i)+'.jpg' for i in range(1, TRAIN_RANGE)]
    copy_files_to_path(dir_base, dir_train_lapiz, fich_nombres)
    fich_nombres = ['Lapiz_'+str(i)+'.jpg' for i in range(TRAIN_RANGE, VALIDATE_RANGE)]
    copy_files_to_path(dir_base, dir_validate_lapiz, fich_nombres)
    fich_nombres = ['Lapiz_'+str(i)+'.jpg' for i in range(VALIDATE_RANGE, TEST_RANGE)]
    copy_files_to_path(dir_base, dir_test_lapiz, fich_nombres)
    
    # Rotulador
    fich_nombres = ['Rotulador_'+str(i)+'.jpg' for i in range(1, TRAIN_RANGE)]
    copy_files_to_path(dir_base, dir_train_rotulador, fich_nombres)
    fich_nombres = ['Rotulador_'+str(i)+'.jpg' for i in range(TRAIN_RANGE, VALIDATE_RANGE)]
    copy_files_to_path(dir_base, dir_validate_rotulador, fich_nombres)
    fich_nombres = ['Rotulador_'+str(i)+'.jpg' for i in range(VALIDATE_RANGE, TEST_RANGE)]
    copy_files_to_path(dir_base, dir_test_rotulador, fich_nombres)

    # Preparacion de las imagenes
    train_datagen = ImageDataGenerator(rescale=1./255)
    valid_datagen = ImageDataGenerator(rescale=1./255)
    # Tama;o de imagen 150x150 en grupos de 20, clasificacion binaria
    # Sparse es mejor?
    train_generator = train_datagen.flow_from_directory(dir_train, target_size=INPUT_SIZE, batch_size=5, class_mode='categorical')
    validation_generator = valid_datagen.flow_from_directory(dir_train, target_size=INPUT_SIZE, batch_size=5, class_mode='categorical')
    model = create_model()
    history = model.fit(train_generator, steps_per_epoch=5, epochs=12, validation_data=validation_generator, validation_steps=3)
    model.save(MODEL_FILENAME)
    print(model.summary())

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


if __name__ == "__main__":
    setup()

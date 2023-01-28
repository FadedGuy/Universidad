# Mitad train 21
# 1/4 validate 11
# 1/4 test 10

import os
import errno
import shutil

from keras import layers
from keras import models
from keras import optimizers

from keras.preprocessing.image import ImageDataGenerator

import matplotlib.pyplot as plt

TRAIN_RANGE = 22
VALIDATE_RANGE = 34
TEST_RANGE = 43

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

def setup():
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

    print(dir_base)

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

if __name__ == "__main__":
    setup()
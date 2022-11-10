import cv2 as cv
import numpy as np

def calc_dsize(img, scale = 1):
    """
    Regresa el dsize requerido para diversas funciones en opencv

    Argumentos
    -------------

    img: Imagen de entrada 
    scale: Factor de escala, dejar en blanco si no es necesario

    """

    return (int(img.shape[1] * scale), int(img.shape[0] * scale))

def calc_m_desp(tcol, trow):
    """
    Calcula la matriz de desplazamiento

    Parameters
    -------------

    tcol: Cantidad de pixeles a moverse en el eje horizontal
    trow: Cantidad de pixeles a moverse en el eje vertical
    """

    return np.float32([[1, 0, tcol], [0, 1, trow]])

def calc_m_rot(deg, scale, px = 0, py = 0):
    """
    Calcula la matriz de de rotacion. Sin pasar px o py el punto de rotacion es (0,0)

    Parameters
    -------------

    deg: Angulo de rotacion en grados
    scale: Factor de escala homogeneo
    px: Punto de rotacion de x 
    py: Punto de rotacion de y 
    """

    return cv.getRotationMatrix2D((px, py), deg, scale)
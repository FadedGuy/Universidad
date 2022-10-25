# -*- coding: cp1252 -*-
#crear la función que añade ruido
import cv2
import numpy as np

def SalyPimienta(img):
    #Normalizamos la imagen a (0-1). Por tanto debe ser real para poder ver
    #variaciones
    img.astype(np.float16,copy = False)
    img = np.multiply(img, 0.00392)#DIvidir por 255

    #Se crea el ruido sal y pimienta
    col,fil= img.shape
    #Números enteros entre 0 y 101
    noise = np.random.randint(101, size=(col,fil))

    #Con esa señal aleatoria se eligen que puntos de la imagen van a ser 0 o 1        
    img = np.where(noise == 0, 0, img)
    img = np.where(noise == 100, 1, img)

    #Recuperams el formato imagen
    ruidosa = cv2.convertScaleAbs(img,alpha=255)
    return ruidosa

def RuidoGaussiano(img,sigma):
    #Normalizamos la imagen a (0-1). Por tanto debe ser real para poder ver
    #variaciones y evitar redondeos
    img.astype(np.float16,copy = False)
    img = np.multiply(img, 0.00392)

    #Se crea el ruido gaussiano
    col,fil= img.shape
    noise = np.random.normal(0, sigma,size=(col,fil))

    # Ruido aditivo
    sumar=img + noise
    ruidosa = cv2.convertScaleAbs(sumar,alpha=255)
    return ruidosa


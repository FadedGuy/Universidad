# -*- coding: cp1252 -*-
import cv2
import numpy as np

#Funci�n para ajuste del contraste entre dos valores ImbMin y UmbMax con un exponente Gamma
def AjusteContraste(Entrada,UmbMin,UmbMax,Gamma):
    #Aplicamos ajuste exponencial partir de los valores VISTOS en el histograma
    fil,col=Entrada.shape
    #Matrices auxiliares
    aux=np.ones(Entrada.shape,np.uint8)
    aux2=np.ones(Entrada.shape,np.uint8)
    resta=np.ones(Entrada.shape,np.uint8)
    img2=np.ones(Entrada.shape,np.float16)
    img3=np.ones(Entrada.shape,np.float16)
    img4=np.ones(Entrada.shape,np.float16)
    #Operador extensi�n
    #1. Eliminamos valores fuera de los umbrales
    aux=np.maximum(Entrada,UmbMin)
    aux2=np.minimum(aux,UmbMax)
    #2. Aplicamos el operador de extensi�n de rango
    resta=np.subtract(aux2,UmbMin)
    img2=np.true_divide(resta,(UmbMax-UmbMin))
    #3. y el exponente
    img3=np.power(img2,Gamma)
    #Recuperamos el formato imagen (si queremos representar en ventana openVC)
    img4=cv2.convertScaleAbs(img3,alpha=255)
    return img4

#Funci�n para obtener la Local Bit Pattern de una zona de la imagen
def CalculoLBP(Entrada):
    pixeles = Entrada.size
    fil,col=Entrada.shape
    #Matriz auxiliar salida
    LBP=np.ones(Entrada.shape,np.uint8)
    #Byte asociado a cada pxel
    Salida=np.array([0,0,0,0,0,0,0,0],np.uint)
    for i in range(fil-1):
        for j in range(col-1):
            Salida[0]=int(Entrada[i,j-1]<Entrada[i,j])
            Salida[1]=int(Entrada[i+1,j-1]<Entrada[i,j])
            Salida[2]=int(Entrada[i+1,j]<Entrada[i,j])
            Salida[3]=int(Entrada[i+1,j+1]<Entrada[i,j])
            Salida[4]=int(Entrada[i,j+1]<Entrada[i,j])
            Salida[5]=int(Entrada[i-1,j+1]<Entrada[i,j])
            Salida[6]=int(Entrada[i-1,j]<Entrada[i,j])
            Salida[7]=int(Entrada[i-1,j-1]<Entrada[i,j])
            LBP[i,j]=Salida[0]*2**7+Salida[1]*2**6+Salida[2]*2**5+Salida[3]*2**4+Salida[4]*2**3+Salida[5]*2**2+Salida[6]*2**1+Salida[7]*2**0
    # cv2.namedWindow("LBP",cv2.WINDOW_NORMAL)
    # cv2.imshow('LBP',LBP)
    #Se suelen calcular los histogramas como medida de comparaci�n
    Histograma=cv2.calcHist([LBP],[0],None,[256],[1,255])
    Histograma = Histograma/pixeles
    return Histograma

#Defiici�n del c�digo de cadena a partir de uno de los contornos proporcionados por
#cv2.findContours()
def codigoCadena(contorno):
    Listaaux=[]
    
##    cadena=np.zeros((1,len(contorno)),np.uint8)
    for jj in range(1,len(contorno)):
        resta=(contorno[jj][0][0]-contorno[jj-1][0][0],contorno[jj][0][1]-contorno[jj-1][0][1])
        if ((resta[1]<0)&(resta[0]>0)):
            Listaaux.append(1)
        if ((resta[1]<0)&(resta[0]==0)):
            for ii in range(abs(resta[1])):
                Listaaux.append(2)
        if ((resta[1]<0)&(resta[0]<0)):
            Listaaux.append(3)
        if ((resta[1]==0)&(resta[0]<0)):
            for ii in range(abs(resta[0])):
                Listaaux.append(4)
        if ((resta[1]>0)&(resta[0]<0)):
            Listaaux.append(5)
        if ((resta[1]>0)&(resta[0]==0)):
            for ii in range(abs(resta[1])):
                Listaaux.append(6)
        if ((resta[1]>0)&(resta[0]>0)):
            Listaaux.append(7)
        if ((resta[1]==0)&(resta[0]>0)):
            for ii in range(abs(resta[0])):
                Listaaux.append(8)
        cadena=np.array(Listaaux)
##        print(contorno[jj],contorno[jj-1],resta)
##        print(cadena[0][jj])
    return cadena

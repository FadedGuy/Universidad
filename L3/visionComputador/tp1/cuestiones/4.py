# Abrir y mostrar imagenes
# Obtener las principales propiedades de la matriz correspondiente a la imagen
# Modificar una imagen (rotación) y crear un fichero nuevo
# Capturamos una imagen con la camara conectada al ordenador
import cv2 as cv
import sys

# Carga la imagen y se verifica que haya sido cargada correctamente
img = cv.imread("img.jpg") 
if img is None:
    sys.exit("No se pudo leer la imagen")

# Mostramos la imagen en una ventana llamada Imagen, la cual permanecera hasta que presionemos una tecla
cv.imshow("Imagen", img)
cv.waitKey(0)
cv.destroyAllWindows()


# Obtener propiedades de la imagen
print(f"Dimensiones: {img.shape}")
print(f"Total pixeles: {img.size}")
print(f"Tipo de datos: {img.dtype}")

# Obtenemos la rotacion a aplicar y la aplicamos y guardamos como img_rotada.jpg
row, col, channel = img.shape
# Point2, angulo, escala
rotation = cv.getRotationMatrix2D(((col-1)/2.0,(row-1)/2.0), 90, 1)
dst = cv.warpAffine(img, rotation, (col, row))
cv.imwrite("img_rotada.jpg", dst)


# Se empieza a capturar video de la webcam
cam = cv.VideoCapture(0)
# Se lee el siguiente frame 
confirmacion, frame = cam.read()
if confirmacion:
    cv.imshow("Capturado", frame)
    cv.waitKey(0)
    cv.destroyAllWindows()
else:
    print("Error al acceder a la camara")

cam.release()
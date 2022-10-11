# Abrir y mostrar imagenes
# Obtener las principales propiedades de la matriz correspondiente a la imagen
# Modificar una imagen (rotación) y crear un fichero nuevo
# Capturamos una imagen con la camara conectada al ordenador
import cv2 as cv

# Carga la imagen y se verifica que haya sido cargada correctamente
img = cv.imread("img.jpg") 
if img is None:
    print("No se pudo abrir la imagen")
    exit()

# Mostramos la imagen en una ventana llamada Imagen, la cual permanecera hasta que presionemos una tecla
cv.namedWindow("Imagen", cv.WINDOW_NORMAL)
cv.imshow("Imagen", img)
cv.waitKey(0)
cv.destroyAllWindows()


# Obtener propiedades de la imagen
print(f"Dimensiones: {img.shape}")
print(f"Total pixeles: {img.size}")
print(f"Tipo de datos: {img.dtype}")

# Obtenemos la rotacion a aplicar la imagen rotada como img_rotada.jpg
row, col, channel = img.shape
# Point2, angulo, escala
rotation = cv.getRotationMatrix2D(((col-1)/2.0,(row-1)/2.0), 90, 1)
dst = cv.warpAffine(img, rotation, (col, row))
cv.imwrite("img_rotada.jpg", dst)


# Se empieza a capturar video de la webcam
cam = cv.VideoCapture(0)
cv.namedWindow("Camara", cv.WINDOW_NORMAL)
# Se lee el siguiente frame 
while True:
    confirmacion, frame = cam.read()
    cv.imshow("Camara", frame)
    if confirmacion:
        key = cv.waitKey(1)&0xFF
        if key == ord("c"):
            cv.namedWindow("Capturado", cv.WINDOW_NORMAL)
            cv.imshow("Capturado", frame)      
        elif key == ord("q"):
            break      
    else:
        break    

cv.destroyAllWindows()
cam.release()
# Abrir y reproducir un fichero de vídeo
# Grabar un vídeo con una cámara y guardar en un fichero
import cv2 as cv

# Abrir y reproducir un fichero de video
video = cv.VideoCapture("video.mp4")
cv.namedWindow("Video", cv.WINDOW_NORMAL)
while video.isOpened():
    confirmacion, frame = video.read()

    # Cuando deje de capturar frames o haya un error al leerlo, se sale del programa
    if not confirmacion:
        print("Error al recibir el siguiente frame")
        break

    cv.imshow("Video", frame)
    # Agregar un mecanismo de salida al presionar q en el teclado
    # El numero dentro de waitkey debe ser lo mas proximo al framerate, si es mas chico estara en
    # slow motion y si es mas grande el contrario
    if cv.waitKey(25) == ord('q'):
        break

video.release()


# Grabar un video con una camara y guardar en un fichero
camera = cv.VideoCapture(0)
if not camera.isOpened():
    print("Error al abrir la camara")
    exit()

# Definimos el codex a usar
fcc = cv.VideoWriter_fourcc(*'MJPG')
# filename, codex, fps, talla
out = cv.VideoWriter('out.mp4', fcc, 20.0, (640, 480))

# Mismo pensamiento que la reproducir desde un fichero 
cv.namedWindow("camara", cv.WINDOW_NORMAL)
while True:
    confirmacion, frame = camera.read()

    if not confirmacion:
        print("Error al recibir el siguiente frame")
        break

    # Para flipear el frame tipo efecto espejo al video (no es lo mismo que rotar)
    # frame = cv.flip(frame, 0)

    # Guardar el frame a out
    out.write(frame)

    cv.imshow('camara', frame)
    # Agregamos shift de bits &0xFF para evitar el overflow, es una medida de precaucion
    key = cv.waitKey(25)&0xFF
    if key == ord('q'):
        break

# Siempre liberamos todo lo que usamos al final
camera.release()
out.release()
cv.destroyAllWindows()
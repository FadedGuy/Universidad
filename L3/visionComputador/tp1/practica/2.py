# Crear un pograma de dibujo de un rectangulo con el raton
import cv2 as cv

# Subrutina que se llamara cada que haya un evento de raton
def dibujar_rectangulo(event, x, y, flags, param):
    # Globales ya que se usaran en el programa principal
    global img_dibujo, x_p, y_p, mouse_pressed

    # Cuando se presione el boton izquierdo
    if event == cv.EVENT_LBUTTONDOWN:
        mouse_pressed = True
        x_p, y_p = x, y
    # Cuando se mueva el mouse
    elif event == cv.EVENT_MOUSEMOVE:
        # Solo modificar el rectangulo si se habia presionado el clic izquierdo anteriormente
        if mouse_pressed:
            #img es una variable de la rutina que llama a dibujar_rectangulo, ya que cv.rectangle 
            # modifica la imagen que se le pasa
            img_dibujo = img.copy()
            cv.rectangle(img_dibujo, (x_p, y_p), (x, y), (0, 255, 0), 10, cv.LINE_4)
    # Cuando se deje de presionar el clic izquierdo
    elif event == cv.EVENT_LBUTTONUP:
        mouse_pressed = False 

# Inicializamos las variables globales
mouse_pressed = False
x_p = 0
y_p = 0

# Abrimos la imagen pato.jpg y creamos una copia
img = cv.imread("pato.jpg")
img_dibujo = img.copy()

cv.namedWindow("Ventana", cv.WINDOW_NORMAL)
cv.setMouseCallback("Ventana", dibujar_rectangulo)

while True:
    cv.imshow("Ventana", img_dibujo)
    key = cv.waitKey(1)&0xFF

    # Al presionar escape y que no estemos dibujando un rectangulo saldremos del programa  
    if key == 27 and not mouse_pressed:
        break

cv.destroyAllWindows()
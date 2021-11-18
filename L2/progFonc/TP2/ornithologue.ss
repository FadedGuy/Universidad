(define albatros 0)
(define mouette 0)
(define cormoran 0)
(define sterne 0)

(define (displayMenu)
  (display "--------------------")(newline)
  (display "MENU")(newline)(newline)
  (display "1- Ajouter un Albatros")(newline)
  (display "2- Ajouter une Mouette")(newline)
  (display "3- Ajouter un Cormoran")(newline)
  (display "4- Ajouter un Sterne")(newline)
  (display "5- Quitter le programme")(newline)(newline)
  (display "Votre choix: ")(newline)
)

(define (ajoute x) (+ x 1))

(define (propDisplay)
  (newline)(display "Nouvelle proportion pourcentuelle")(newline)
  (let ((total (+ albatros mouette cormoran sterne)))
    (display "Albatros: ")(display (* (/ albatros total) 100.0))(display "%")(newline)
    (display "Mouette: ")(display (* (/ mouette total) 100.0))(display "%")(newline)
    (display "Cormoran: ")(display (* (/ cormoran total) 100.0))(display "%")(newline)
    (display "Sterne: ")(display (* (/ sterne total) 100.0))(display "%")(newline)
    (display "Total d'oiseaux: ")(display total)(newline)
    )
)

(define (propOiseaux)
  (begin
    (displayMenu)
    (let ((op (read)))
      (cond ((equal? op 1) (begin
                              (set! albatros (ajoute albatros))
                              (propDisplay)(propOiseaux)))
            ((equal? op 2) (begin
                              (set! mouette (ajoute mouette))
                              (propDisplay)(propOiseaux)))
            ((equal? op 3) (begin
                              (set! cormoran (ajoute cormoran))
                              (propDisplay)(propOiseaux)))
            ((equal? op 4) (begin
                              (set! sterne (ajoute sterne))
                              (propDisplay)(propOiseaux)))
            ((equal? op 5) (display "Chao !")(newline))
            (else (display "erreur de saisie")(newline)(propOiseaux))))))


(propOiseaux)
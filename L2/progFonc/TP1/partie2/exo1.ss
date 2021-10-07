(define (emballer-100 nb)
  (quotient nb 100)
  )

(define (emballer-50 nb)
  (quotient nb 50)
  )

(define (emballer-10 nb)
  (quotient nb 10)
  )

(define (emballer_100 nb)
  (display (emballer-100 nb)) (display " boite(s) de 100 remplie(s)") (newline)
  (- nb (* (emballer-100 nb) 100))
  )

(define (emballer_50 nb)
  (display (emballer-50 nb)) (display " boite(s) de 50 remplie(s)") (newline)
  (- nb (* (emballer-50 nb) 50))
  )

(define (emballer_10 nb)
  (display (emballer-10 nb)) (display " boite(s) de 10 remplie(s)") (newline)
  (- nb (* (emballer-10 nb) 10))
  )

(define (emballer_tout)
  (display "Saisie quantite des disquettes : ")
  (let ((disq (read))
        )
    (if (= 0 (remainder disq 10))
        (begin
          (emballer_10 (emballer_50 (emballer_100 disq)))
          (display "Emballage terminé !") (newline)
          )
        (begin
          (display "Saisie incorrect, c'est pas une multiple de 10 ! ")(newline)
         )
          )
    
   )
  )

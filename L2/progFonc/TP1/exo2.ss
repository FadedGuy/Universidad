; 100, 50, 10 plus grande, multiple de 10

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

(define (emballer_tout nb)
  (emballer_10 (emballer_50 (emballer_100 nb)))
  (display "Emballage terminé !") (newline)
  )

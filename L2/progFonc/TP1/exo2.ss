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

(define (f x y)
  (+ (/ (- x 3) (+ (* y y) 1)) (/ 1 (+ (* x x x) 3)))
  )

(define (cel C)
  (+ (* (/ 9 5) C) 32)
  )

;sqrt xB - xA ^ 2 + yB - yA ^ 2
(define (distance xA yA xB yB)
  (sqrt(+ (expt (- xB xA) 2) (expt (- yB yA) 2)))
  )

(define (m min)
  (* min 60)
  )

(define (h heure)
  (m heure)
  )

(define (hSec heure min sec)
  (+ sec (m min) (h (m heure)))
  )

;n1*c1 + n2*c2 / n1+n2
(define (moy-pond n1 n2 c1 c2)
  (/ (+ (* n1 c1) (* n2 c2)) (+ c1 c2))
  )
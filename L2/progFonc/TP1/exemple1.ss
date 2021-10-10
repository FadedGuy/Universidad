(* 4 5)
; -----------

(define (carre x)
  (* x x))

(carre 12)
;---------

(define (hypotenuse cote1 cote2)
  (sqrt (+ (carre cote1) (carre cote2))))

(hypotenuse 5 4)
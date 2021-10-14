(define (nbj-mars an)
  (let ((a (remainder an 19)) (b (remainder an 4)) (c (remainder an 7)))
    (let ((d (remainder (+ (* 19 a) 24) 30)))
      (let ((e (remainder (+ (* 2 b) (* 4 c) (* 6 d) 5) 7)))
        (+ 22 d e)
      )
    )
  )
)

(define (mois jours)
  (if (> jours 31)
      "avril"
      "mai"
  )
)

(define (jour jours)
  (if (> jours 31)
      (- jours 31)
      jours
  )
)

(define (affiche-paques an)
  (let ((jours (nbj-mars an)))
    (display (jour jours))(display " ")(display (mois jours))(display " ")(display an)(newline)
  )
)

(affiche-paques 1998)
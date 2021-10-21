(load "libcalc.ss") ;loads libcalc file
(#%require racket/trace)

(define (add a b)
  (if (sup_egal? a b)
      (if (non_zero? b)
          (add (incrementer a) (decrementer b))
          a
      )
  )
)

(define (sou a b)
  (if (sup_egal? a b)
      (if (non_zero? b)
          (sou (decrementer a) (decrementer b))
          a
      )
  )
)

(define (mul a b)
  (if (non_zero? b)
      (if (sup_egal? b 2)
          (add (mul a (decrementer b)) a)
          a
      )
      0
   )
)

(define (div a b)
  (if (non_zero? b)
      (if (sup_egal? b 2)
          (sou a (div a (decrementer b)))
          a
      )
      0
  )
)

(trace div)
(div 4 2)
(untrace div)

;(calculet)

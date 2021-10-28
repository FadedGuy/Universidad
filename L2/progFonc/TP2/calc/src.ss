(load "grafcalc.ss") ;loads graphic calculator
(load "libcalc.ss") ;loads libcalc file
(#%require racket/trace)

(define (add a b)
  (if (sup_egal? a b)
      (if (non_zero? b)
          (add (incrementer a) (decrementer b))
          a
      )
      1
  )
)

(define (sou a b)
  (if (sup_egal? a b)
      (if (non_zero? b)
          (sou (decrementer a) (decrementer b))
          a
      )
      1
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
      (if (sup_egal? b a)
          (if (and (sup_egal? b a) (sup_egal? a b))
              1
              0
          )
          (add (div (sou a b) b) 1)
      )
      'indefini
  )
)

(trace add)
(add 3 2)
(untrace add)
(trace sou)
(sou 3 2)
(untrace sou)
(trace mul)
(mul 3 2)
(untrace mul)
(trace div)
(div 3 2)
(untrace div)

;(calculet)

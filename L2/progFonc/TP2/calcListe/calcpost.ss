(load "operateurs.ss")

(define resultat 0)

(define (calcpost l)
  (cond ((null? l) (display "resultat: ")(display resultat)(newline))
        ((number? (car l)) (display "number")(newline)(calcpost (cdr l)))
        ((fonction? (car l)) (display "symbole")(newline) (calcpost (cdr l)))
        (else (display "Valeur non etendue")(newline))))

(calcpost '(7 3 + 16 sqrt *))
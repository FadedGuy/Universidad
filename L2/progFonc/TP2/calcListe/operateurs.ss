; operateurs.ss
; Programmation fonctionnelle TP3, listes exercice optionnel 
; (c) Eric Gouardères , Mars 2015

(#%require Scheme)

; déterminer si un symbole est un symbole d'opérateur
(define fonction? (lambda (f)
                   (procedure? (eval f (interaction-environment)))))

; déterminer l'arité d'une fonction
; retourne un entier correspondant à l'arité de la fonction, -1 pour une fonction n-aire

(define arite (lambda (f)
                (let ((nbarg (procedure-arity (eval f (interaction-environment)))))
                  (if (integer? nbarg)
                      nbarg
                      -1))))
                    
; appliquer un symbole d'opérateur à une liste d'arguments
(define evaluer (lambda (f larg)
                  (apply (eval f (interaction-environment)) larg)))

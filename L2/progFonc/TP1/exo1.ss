(define (prixttc1 TVA prixHT)
  (+ prixHT (* (/ TVA 100) prixHT))
  )

(define (prixttc2 TVA prixHT)
  (display "Prix HT : ") (display prixHT) (newline)
  (display "TVA     : ") (display TVA) (newline)
  (display "-------------------") (newline)
  (display "Prix TTC: ") (display (prixttc1 TVA prixHT)) (newline)  
  )


(define TVAttc3 15)
(define (prixttc3 prixHT)
  (prixttc2 TVAttc3 prixHT)
  )

(define (prixttc4)
  (display "Saisie le prixHT: ")
  (prixttc2 TVAttc3 (read))
  )
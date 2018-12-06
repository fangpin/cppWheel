(define (smallest-divisor n)
  (define (iter k)
    (cond ((> (* k k) n) n)
          ((divide? n k) k)
          (else (iter (next k)))))
  (iter 2))

(define (divide? n k)
  (= (remainder n k) 0))

(define (next divisor)
  (if (= divisor 2)
      3
      (+ divisor 2)))

(display (smallest-divisor 199))
(display " ")
(display (smallest-divisor 1999))
(display " ")
(display (smallest-divisor 19999))

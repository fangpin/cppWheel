(define (pasckal n m)
  (if (or
       (= m 1)
       (= n m))
      1
      (+ (pasckal (- n 1)
                  (- m 1))
         (pasckal (- n 1) m))))


(display (pasckal 3 2))
(display (pasckal 5 2))
(display (pasckal 2 2))
(display (pasckal 3 1))

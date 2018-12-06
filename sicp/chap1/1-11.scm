(define (recursion-f n)
  (if (<= n 3)
      n
      (+ (recursion-f (- n 1))
         (* 2 (recursion-f (- n 2)))
         (* 3 (recursion-f (- n 3))))))


(define (f n)
  (define (iter a b c count)
    (if (= count 3)
        c
        (iter b c (+ (* 3 a)
                       (* 2 b)
                       c)
                (- count 1)))
    )
  (iter 1 2 3 n))

(display (recursion-f 5))
(display (f 5))

(define (double n)
  (* n 2))

(define (halve n)
  (/ n 2))

(define (even n)
  (= (remainder n 2) 0))

(define (recursion-fast-multi a b)
  (cond ((= b 0) 0)
        ((even b) (recursion-fast-multi (double a) (halve b)))
        (else (+ a (recursion-fast-multi a (- b 1))))))

(define (fast-multi x y)
  (define (iter a b c)
    (cond ((= c 0) a)
          ((even c) (iter a (double b) (halve c)))
          (else (iter (+ a b) b (- c 1)))))
  (iter 0 x y))


;; (display (recursion-fast-multi 5 7))
(display (fast-multi 5 7))

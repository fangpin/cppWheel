(define (sum-of-bigger-two x y z)
  (cond ((and (< x y) (< x z)) (+ y z))
  ((and (< y z) (< y x)) (+ x z))
  ((and (< z x) (< z y)) (+ x y))))

(display (sum-of-bigger-two 1 2 3))
;; (display (sum-of-bigger-two 2 1 3))

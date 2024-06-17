;; Scheme ;;

;; Q1 ;;
(define (over-or-under x y)
  (if (< x y)
    -1
    (if (= x y)
      0
      1
    )
  )
)

;;; Tests
(over-or-under 1 2)
; expect -1
(over-or-under 2 1)
; expect 1
(over-or-under 1 1)
; expect 0

;; Q2 ;;
(define (filter-lst f lst)
  (if (equal? (cdr lst) nil)
    (if (f (car lst))
      lst
      nil
    )
    (if (f (car lst))
      (cons (car lst) (filter-lst f (cdr lst)))
      (filter-lst f (cdr lst))
    )
  )
)

;;; Tests
(define (even? x)
  (= (modulo x 2) 0))
(filter-lst even? '(0 1 1 2 3 5 8))
; expect (0 2 8)

;; Q3 ;;
(define (make-adder num)
  (lambda (x) (+ x num))
)

;;; Tests
(define adder (make-adder 5))
(adder 8)
; expect 13

;; Q4 ;;
(define lst
  (cons (cons 1 nil) (cons 2 (cons (cons 3 (cons 4 nil)) (cons 5 nil)))) 
)

;; Q5 ;;
(define (composed f g)
  (lambda (x) (f (g x)))
)

;; Q6 ;;
(define (remove item lst)
  (if (equal? lst nil)
    nil
    (filter-lst (lambda(x) (not(= x item))) lst))
)


;;; Tests
(remove 3 nil)
; expect ()
(remove 3 '(1 3 5))
; expect (1 5)
(remove 5 '(5 3 5 5 1 4 5 4))
; expect (3 1 4 4)

;; Q7 ;;
(define (no-repeats s)
  (if (equal? s nil)
    nil
    (cons (car s) (remove (car s) (no-repeats (cdr s))))
  )
)

;; Q8 ;;
(define (substitute s old new)
  (if (equal? s nil)
    nil
    (if (equal? (car s) old)
      (cons new (substitute (cdr s) old new))
      (cons (car s) (substitute (cdr s) old new))
    )
  )
)

;; Q9 ;;
(define (sub-all s olds news)
  (if (equal? s nil)
    nil
    (if (equal? olds nil)
      s
      (sub-all (substitute s (car olds) (car news)) (cdr olds) (cdr news))
    )
  )
)
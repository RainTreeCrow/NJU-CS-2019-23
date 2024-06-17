;;;;;;;;;;;;;;;
;; Questions ;;
;;;;;;;;;;;;;;;

; Scheme

(define (cddr s)
  (cdr (cdr s))
)

(define (cadr s)
  (car (cdr s))
)

(define (caddr s)
  (car (cdr (cdr s)))
)

; not using fliter
(define (unique s)
    (define (remove item lst)
        (if (equal? lst nil)
            nil
            (if (equal? (car lst) item)
                (remove item (cdr lst))
                (cons (car lst) (remove item (cdr lst)))
            )
        )
    )
    (if (equal? s nil)
    nil
    (cons (car s) (remove (car s) (unique (cdr s))))
  )
)

; using fliter
(define (unique s)
    (if (equal? s nil)
        nil
        (cons (car s)
            (unique (filter (lambda (x) (not (equal? x (car s)))) (cdr s)))))
)

(define (cons-all first rests)
    (map (lambda (x) (cons first x)) rests)
)

;; List all ways to make change for TOTAL with DENOMS
(define (list-change total denoms)
    (define (make-list x len)
        (if (= len 1)
            (cons x nil)
            (cons x (make-list x (- len 1)))
        )
    )
    (if (or (equal? denoms nil) (= total 0))
        nil
        (if (> (car denoms) total)
            (list-change total (cdr denoms))
            (if (and (equal? (cdr denoms) nil) (equal? 0 (remainder total (car denoms))))
                (cons (make-list (car denoms) (/ total (car denoms))) nil)
                (append
                    (if (equal? total (car denoms))
                        (cons (make-list (car denoms) 1) nil)
                        nil
                    )
                    (cons-all (car denoms) (list-change (- total (car denoms)) denoms))
                    (list-change total (cdr denoms))
                )
             )
        )
    )
)

; Tail recursion

(define (replicate x n) 
    (define (helper x n l)
        (if (= 0 n)
            l
            (helper x (- n 1) (cons x l))
        )
    )
    (helper x n nil)
)


(define (accumulate combiner start n term)
    (if (= 0 n)
        start
        (combiner (accumulate combiner start (- n 1) term) (term n))
    )
)

(define (accumulate-tail combiner start n term)
    (if (= 0 n)
        start
        (accumulate-tail combiner (combiner start (term n)) (- n 1) term)
    )
)


; Macros

(define-macro (list-of map-expr for var in lst if filter-expr)
    (list 'map (list 'lambda (list var) map-expr) (list 'filter (list 'lambda (list var) filter-expr) lst))
)
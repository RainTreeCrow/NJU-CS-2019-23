;; Lab 12: Macros ;;

;; Q3 ;;
(define (repeatedly-cube n x)
    (if (zero? n)
        x
        (let (
                (y (repeatedly-cube (- n 1) x))
               )
                (* y y y)
        )
    )
)

;; Q4 ;;
(define-macro (def func bindings body)
    `(define ,func (lambda ,bindings ,body))
)

;; Q5 ;;
(define-macro (switch expr cases)
    (cons 'cond 
        (map (lambda (x) (cons `(equal? ,expr ,(car x)) (cdr x))) cases))
)
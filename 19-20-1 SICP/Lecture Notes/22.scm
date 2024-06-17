;; Expressions as Data

(define x 2)
'x
x
(eval 'x)
'(1 2 3)
'(+ 1 2)
(eval '(+ 1 2))
'(if (= x 2) 5 6)
(eval '(if (= x 2) 5 6))
(list 'if (list '= 'x 2) 5 6)
(eval (list 'if (list '= 'x 2) 5 6))
(list if (list '= 'x 2) 5 6) 
(list 'if (list '= x 2) 5 6)

(define and-expr '(and 5 (= 7 8) 9))
and-expr
(eval and-expr)
(define (make-and-expr e1 e2)
	(list 'and e1 e2))
(make-and-expr #t #f)
(eval (make-and-expr #t #f))
(make-and-expr '(= 0 1) '(/ 1 0))
(eval (make-and-expr '(= 0 1) '(/ 1 0))) 

;; Begin
(begin (print 1) (print 2) (print 3))
(begin (define x 1) (define y 2) (+ x y))

;; Let
(let ((a 1)
	  (b (+ 2 3)))
	(+ a b))

(let ((a 1)
	  (b (+ a 2)))
	(+ a b))

;; Macros

;Double
(define (double expr)
	(begin expr expr)) 
(double (print 2)) ;; Evaluates argument before calling
(double '(print 2)) ;; expr is treated as a list inside the function

(define (double expr)
	(list 'begin expr expr))
(double '(print 2)) ;; Returns (begin (print 2) (print 2))
(eval (double '(print 2)))

(define-macro (double expr)
	(list 'begin expr expr)) 
(double (print 2)) ;; Same as (eval '(begin (print 2) (print 2)))

; add-to
(define x 1)
(define x (+ x (+ 1 2))) ;; Expression equivalent to (add-to x (+ 1 2))
'(define x (+ x (+ 1 2))) ;; The expression we want to create in the macro

(define-macro (add-to var expr)
	(list 'define var (list '+ var expr)))
(add-to x (+ 3 4)) ;; Same as (eval '(define x (+ x (+ 1 2))))
(define y 0)
(add-to y x) ;; Same as (eval '(define y (+ y x)))

; for
(map (lambda (x) (* x 2)) (list 1 2 3 4)) ;; Equivalent to (for x in (list 1 2 3 4) do (* x 2))
'(map (lambda (x) (* x 2)) (list 1 2 3 4)) ;; The expression we want to create

(define-macro (for var in lst do expr)
	(list 'map (list 'lambda (list var) expr) lst))
(for y in '(1 2 3 4) do (+ y 2)) ;; Same as (eval '(map (lambda (y) (+ y 2)) '(1 2 3 4)))

;; Quasi-quoting
(define x 2)
'(1 x 3)
(list 1 2 3)
`(1 ,x 3)
`(1 x 3)
`(1 (+ ,x 5) 3)
`(1 ,(+ x 5 3))
`(,x y z)

; Macros with quasiquoting
(define-macro (twice expr)
	`(begin ,expr ,expr))

(define-macro (add-to sym expr)
	`(define ,sym (+ ,sym ,expr)))

(define-macro (for var in lst do expr)
	`(map (lambda (,var) ,expr) ,lst))

(define ones (cons-stream 1 ones))

(define (nats start)
	(cons-stream start (nats (+ start 1))))

(define (add-stream s1 s2)
    (cons-stream (+ (car s1) (car s2))
                  (add-stream (cdr-stream s1) (cdr-stream s2))))

(define allNats (cons-stream 1(add-stream ones allNats)))

(define (gerN str n)
	(if (= n 0)
		nil
		(cons (car str) (getN (cdr-stream str) (- n 1)))))

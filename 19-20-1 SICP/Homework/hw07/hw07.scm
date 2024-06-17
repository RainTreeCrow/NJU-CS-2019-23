(define (map-stream f s)
  (if (null? s)
      nil
      (cons-stream (f (car s)) (map-stream f (cdr-stream s)))))

(define multiples-of-three
  (cons-stream 3 (map-stream (lambda (x) (+ x 3)) multiples-of-three))
)

(define multiples-of-three
  (map-stream (lambda (x) (+ x 3)) (cons-stream 0 multiples-of-three))
)

(define (rle s)
  (if (null? s)
      nil
      (if (null? (cdr-stream s))
          (cons-stream (cons (car s) (cons 1 nil)) nil)
          (if (= (car s) (car (cdr-stream s)))
              (cons-stream (cons (car (car (rle (cdr-stream s)))) (cons (+ 1 (car (cdr (car (rle (cdr-stream s)))))) nil)) (cdr-stream (rle (cdr-stream s))))
              (cons-stream (cons (car s) (cons 1 nil)) (rle (cdr-stream s))))))
)

(define (list-to-stream l)
  (if (null? l)
      nil
      (cons-stream (car l) (list-to-stream (cdr l))))
)

(define (stream-to-list s)
  (if (null? s)
      nil
      (cons (car s)
            (stream-to-list (cdr-stream s))))
)


(defun print-tree (tree)
    (
        ;(inorder (tree))
        cond
        
        ((null tree) (terpri))
        ((atom(car tree))  (write(car tree)) (print-tree (cdr tree)))
        (t (write(cdr tree)) (print-tree (cdr tree)))
    )
)
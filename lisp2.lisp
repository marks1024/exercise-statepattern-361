
(defun print-tree (tree)
    (
        (inorder (tree))
        ;cond
        
        ;((null tree) (terpri))
        ;((atom(car tree))  (write(car tree)) (print-tree (cdr tree)))
        ;(t (write(cdr tree)) (print-tree (cdr tree)))
    )
)

defun atom(tree)(
    (car tree)
)
defun leftChilds(tree)(
    (cadr tree)
)
defun rightChilds(tree)(
    (caddr tree)
)

(defun inorder (tree)
(cond ((null tree))
(t (inorder (leftChilds tree))

(print (atom tree))
(inorder (rightChilds tree)))))

(defun nextlevel ( treelist )
   ( cond
      (( null treelist ) nil )
      (t ( append ( cdar treelist ) ( nextlevel ( cdr treelist ))))
   
   )
)

(defun printheads( treelist elem )
   ( cond
      (( null treelist ) (terpri))
      (t (+ elem (cdaar treelist))( write ( caar treelist )) ( printheads ( cdr treelist elem )))
   )
)

;(defun changeNumber (treelist, elem)

;)


(defun print-treelist (treelist elem)
    (cond
        ((null treelist))
        (t (printheads treelist elem) (print-treelist ( nextlevel treelist )))
    )
)

( defun print-tree ( tree )
   ( setq elem 0 )
   ( print-treelist ( (list tree) elem ) )
)


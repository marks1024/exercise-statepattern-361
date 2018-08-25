
(defun nextlevel ( treelist )
   ( cond
      (( null treelist ) nil )
      (t ( append ( cdar treelist ) ( nextlevel ( cdr treelist ))))
   
   )
)

(defun printheads( treelist )
   ( cond
      (( null treelist ) (terpri))
      (t ( write ( caar treelist )) (printChilds (car treelist)) ( printheads ( cdr treelist )))
   )
)

(defun printChilds( treelist)
    (cond 
    (( null treelist ) (terpri) )
    (t ( write ( caadr treelist)) (values) (printChilds (cdr treelist)))
    ;(t ( append ( cdar treelist ) ( nextlevel ( cdr treelist ))))
    )
)


(defun print-treelist (treelist)
    (cond
        
        ((null treelist))
        (t (printheads treelist) (print-treelist ( nextlevel treelist )))
    )
)

( defun print-tree ( tree )
   ( print-treelist ( list tree ) )
)

;(setq tree (read))
;(print-tree(tree))
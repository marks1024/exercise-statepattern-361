
(defun nextlevel ( treelist )
   ( cond
      (( null treelist ) nil )
      (t ( append ( cdar treelist ) ( nextlevel ( cdr treelist ))))
   
   )
)

(defun printheads( treelist )
   ( cond
      (( null treelist ) (terpri))
      (t ( write ( caar treelist )) ( printheads ( cdr treelist )))
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

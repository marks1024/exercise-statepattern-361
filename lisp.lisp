;(setq *print-case* :capitali(A (B (C (D)) (E (F) (G (H)))) (J (K (L (M) (N (P))))))ze)

;(defvar *age* 18)
;(defvar *num-3* 5)

;(defun get-school (age)
   ; (case age
            ;(5 (print "Kindergarden"))
            ;(6 (print "First Grade"))
            ;(otherwise (print "middle school"))
    ;))
;(get-school *age*)

;(setq tree (read))
(setq tree (list '(A (B (C (D)) (E (F) (G (H)))) (J (K (L (M) (N (P))))))))

;(car tree)
;(setq *var* (car tree))
(format t "First is ~a ~%" (car tree))




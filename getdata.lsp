(defun c:getdata ( / a cc e eg en et n p p0 ps s x y z f)
    (setq f (open "e:/fdb/pline.dat" "w"));;;打开文件
    (setq a (ssget '((0 . "polyline"))))
    (setq aa (dxfcod -1 a))
    (write-line (rtos (length aa) 2 0 ) f);;;线段数量
    (setq count 0)
    (foreach p aa
        (setq e (cdr p))
        (setq en (entnext e))
        (setq eg (entget en))
        (setq p (cdr (assoc 10 eg)) p0 p)
        
        (setq x (car p))
        (setq y (cadr p))
        (setq z (caddr p))
        (setq p (list x y z))
        (setq ps p)
        (setq bb '(nil))
        (setq bb (cons p bb))
        (setq cc nil)
        (setq cc (cons p cc))
        (setq n 1)
        (setq et "VERTEX")
        (setq count (+ count 1))
        (print count)
        (while (= et "VERTEX")
            (setq e en)
            (setq en (entnext e))
            (setq eg (entget en))
            (setq et (cdr (assoc 0 eg)))
            (if (= et "VERTEX")
                (progn
                    (setq p (cdr (assoc 10 eg)))
                    (setq n (+ n 1))
                    (setq x (car p))
                    (setq y (cadr p))
                    (setq z (caddr p))
                    (setq p (list x y z))
                    (setq s (distance ps p))
                    (if (> s 0)
                        (progn
                            (setq bb (cons p bb))
                            (setq ps p)
                        )
                    )
                )
            )
        )
        ;;;每段 polyline 输出
        (write-line (rtos 2 2 0 ) f);;;线段颜色
        (write-line (rtos 3 2 0 ) f);;;显示时间
        (write-line (rtos (- (length bb) 1) 2 0)  f)
        ;;;(print (length bb))
        (foreach p bb
            ;;;(print p)
            ;;;x y z 对应OpenGL中的x -z y，所以 car caddr -cadr
            (if (/= p nil)
                (write-line (strcat (rtos (car p) 2 5) "," (rtos(caddr p) 2 5) ","(rtos(- (cadr p)) 2 5)) f)
            )
        )
        ;;;(write-line (strcat (rtos (car pt) 2 5) "," (rtos(cadr pt) 2 5) ",") f)
        
    )
    (close f)
)

(defun dxfcod (numbe ssent / vl len k ai g dxfvl) ; 参数1：dxf组码 参数2：选择集。返回对应选择集的dxf组码表
    (setq vl '())
    (if ssent
        (progn
            (setq len (sslength ssent)k 0)
            (repeat len
                (setq ai (ssname ssent k)k (1+ k))
                (setq g (entget ai))
                (setq dxfvl (assoc numbe g))
                (setq vl (append vl(list dxfvl)))
            )
        )
        (setq vl nil)
    )
    (setq vl vl)
)
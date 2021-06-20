(defun c:getdata ( / a cc e en et n p0 ps s x y z f numpolylines)
    (setq f (open "e:/fdb/pline.dat" "w"));;;打开文件
    (setq a (ssget '((0 . "polyline"))))
    (setq aa (dxfcod -1 a))
    (setq numpolylines (length aa) )
    (write-line (rtos numpolylines 2 0 ) f);;;线段数量
    (setq count 0)
    (foreach p aa   ;;;循环处理每一根线
        (setq e (cdr p))
        (setq en (entnext e))
        (setq eg (entget en))
        (setq p (cdr (assoc 10 eg)) p0 p)
        (setq color (cdr (assoc 62 eg)))
        (setq time (read (cdr (assoc 8 eg))))
        ;;;(prin1 "color is " )(print color)
        
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
        (setq ratio (* 100 (/ (float count) numpolylines)))
        ;;;(setq ratio (inte ratio))
        (print ratio)
        (princ " % ")
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
        (write-line (rtos color 2 0 ) f);;;线段颜色
        (write-line (rtos time 2 0 ) f);;;显示时间
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
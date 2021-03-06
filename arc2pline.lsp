(defun arc->pline(ent h / xtblm xtblz db r po a0 h n)
   (setq xtblm '("cmdecho" "osmode")
        xtblz (mapcar 'getvar xtblm)
        db (entget ent)  r (cdr (assoc 40 db))
        po (cdr (assoc 10 db))  
        a0 (cdr (assoc 50 db))
        db (- (cdr (assoc 51 db)) a0)
        db (cond ((< db 0) (+ (* 2.0 pi) db))
        (t               db)
        )
        ;;;n  (fix (/ db (atan (/ (sqrt (- (* 2.0 r h) (* h h))) (- r h)))))
        n h
        db (/ db n)
   )
   (mapcar 'setvar xtblm '(0 0))
   (command "3dpoly" (polar po a0 r))
   (repeat n (command (polar po (setq a0 (+ a0 db)) r)))
   (command "" "_matchprop" ent (entlast) "" "_erase" ent "" "redraw")
   (mapcar 'setvar xtblm xtblz)(princ)
   (princ n) (princ " 段线")
)

(defun c:cc()
   (setq t0 (getvar "cdate"))
   (princ "输入要产生线段的段数：")
   (setq num (getint))
   (arc->pline (car (entsel "\n请选取要转化多段线的圆弧:")) num)
   ;;;(princ (strcat "\n耗时：" (rtos (* 1000000 (- (getvar "cdate") t0) 2 3)) "秒"))
   (princ)
)

(princ "Enter Radius: ")(setq radius (read))
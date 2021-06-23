(defun c:od ()
    (setvar "cmdecho" 1) ;防止命令执行过程显示
    (setvar "osmode" 0)
    ;;;(print"输入od起点")(setq sp(getpoint))(print"输入od终点")(setq ep(getpoint sp))(command "ucs" sp ep  (polar sp (/ pi 2.0) 10.0))
    (print"od start")
    (setq sp(getpoint))
    (print"od end")
    (setq ep(getpoint sp))
    (setq r (/ (distance sp ep) 2.))
    (setq ang (angle sp ep))
    (setq ang (/ (* ang 180.0) pi))
    ;;;(command "ucs" sp (command (polar (/ sp (* ang 180.0) pi))))
    ;;;(command "line" sp ep "")(command "ucs" sp ep "")
    ;;;(setq zp (list (car sp) (cadr sp) 10))
    ;;;(command "line" (list sp) (list ep) "")
    ;;;(command "line" sp ep "")
    ;(command "ucs" sp ep  (polar sp (/ pi 2.0) 10.0))
    (setq ang (angle sp ep))
    ;;;((command "ucs" "z" (/ (* ang 180.0) pi)))
    (command "ucs" sp "")
    (command "ucs" "z" (/ (* ang 180.0) pi))
    
    (command "ucs" "x" 90)
    
    
    (setq cen (polar '(0 0 0) 0 r))
    (setq num 100)
    (setq ang pi)
    (setq delta (/ pi 100.))


    (command "3dpoly" (polar cen ang r))(repeat num (command (polar cen (setq ang (- ang delta)) r)))
    (command "")
    (command "ucs" "w")
    
    ;;;(command "3dpoly" )
    ;;;(repeat n (command (polar cen (setq ang (- ang pi/100.0 )) r)))
    
    ;;;(repeat 3
    ;;;(setq s1 (0 0 0))
    ;;;(setq s2 (1 1 0))
    ;;;(setq s3 (2 0 0))

    ;;;(command "rectang" ep zp )

    ;;;(command "line" (list sp) (list ep) "")
    ;;;(command "line" (list s2) (list s3) "")
    (princ)
    (setvar "cmdecho" 1) ;防止命令执行过程显示
)

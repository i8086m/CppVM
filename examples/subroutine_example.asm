call PRINT
ret

lbl_PRINT
call CLEAR
call LOAD
call PRNT
ret

lbl_CLEAR
cls
ret

lbl_LOAD
mov8 a 5
ret

lbl_PRNT
put
ret
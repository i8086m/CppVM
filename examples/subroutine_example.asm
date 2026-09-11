call print
ret

print:
call clear
call load
call prnt
ret

clear:
cls
ret

load:
mov8 a 5
ret

prnt:
put
ret
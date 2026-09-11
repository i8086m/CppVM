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
mov a 5
ret

prnt:
put
ret
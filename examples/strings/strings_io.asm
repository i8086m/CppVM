import modules/strings.asm


mov a string
mov b 10
call getstr
; Ввод строки не длиннее 10 символов

mov b 0

loop:
inc b
exch
mov a string
call putstr
exch
mov a b
cmp 10
jnz loop

; Вывести строку 10 раз

getkey
ret


string:
0 0 0 0 0 0
0 0 0 0 0 0
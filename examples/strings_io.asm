import strings


mov a string
mov8 b 10
call getstr
# Ввод строки не длиннее 10 символов

mov8 b 0

lbl_loop
inc b
exch
mov a string
call putstr
exch
mov a b
cmp 10
jnz loop

# Вывести строку 10 раз

ret


lbl_string
0 0 0 0 0 0
0 0 0 0 0 0
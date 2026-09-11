cls

mov a 16
putc

mov a 32
putc

mov a 67
putc
mov a 97
putc
mov a 108
putc
mov a 99
putc

mov a 32
putc

mov a 17
putc

endl

mov a 65
putc
mov a 58
putc

cin
mov b a

mov a 79
putc
mov a 112
putc
mov a 58
putc

cin
wr a 0 240

mov a 66
putc
mov a 58
putc

cin
mov c a

ld a 0 240

cmp 1
jz SUM
cmp 2
jz SUB
cmp 3
jz MUL
cmp 4
jz DIV
jmp KON

lbl_SUM
add b c
mov a b
put
jmp KON

lbl_SUB
sub b c
mov a b
put
jmp KON

lbl_MUL
mul b c
mov a b
put
jmp KON

lbl_DIV
div b c
mov a b
put
jmp KON

lbl_KON
endl
getkey
jmp 0 0

ide
dbg
ret
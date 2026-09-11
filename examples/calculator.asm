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
wr a 240

mov a 66
putc
mov a 58
putc

cin
mov c a

ld a 240

cmp 1
jz SUM
cmp 2
jz SUB
cmp 3
jz MUL
cmp 4
jz DIV
jmp KON

SUM:
add b c
mov a b
jmp KON

SUB:
sub b c
mov a b
jmp KON

MUL:
mul b c
mov a b
jmp KON

DIV:
div b c
mov a b
jmp KON

KON:
puts
endl
getkey
jmp 0

noinf
ret
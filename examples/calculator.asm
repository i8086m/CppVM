cls

mov8 a 16
putc

mov8 a 32
putc

mov8 a 67
putc
mov8 a 97
putc
mov8 a 108
putc
mov8 a 99
putc

mov8 a 32
putc

mov8 a 17
putc

endl

mov8 a 65
putc
mov8 a 58
putc

cin
mov b a

mov8 a 79
putc
mov8 a 112
putc
mov8 a 58
putc

cin
wr a 0 240

mov8 a 66
putc
mov8 a 58
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
jmp 0 0

noinf
ret
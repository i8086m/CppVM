cls
ld bc DB1
lbl_RB
ld a bc
putc
inc c
cmp *!
jz STP
jmp RB

lbl_DB1
*h
*e
*l
*l
*o
32
*w
*o
*r
*l
*d
*!

lbl_STP
dbg
ide
cin
ret
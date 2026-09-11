cls
mov c string

lbl_loop
ld a (c)
putc
inc c
cmp *!
jz exit
jmp loop

lbl_string
*h
*e
*l
*l
*o
*,
*w
*o
*r
*l
*d
*!

lbl_EXIT
dbg
ide
cin
ret
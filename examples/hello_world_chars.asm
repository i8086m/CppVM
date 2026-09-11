cls
mov c string

loop:
ld a c
cmp 0
jz exit
putc
inc c
jmp loop

string:
'H'
'e'
'l'
'l'
'o'
','
' '
'w'
'o'
'r'
'l'
'd'
'!'
0

exit:
noinf
cin
ret
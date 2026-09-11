lbl_main
cls
call draw
call mark
jmp main


lbl_mark
mov c field
getkey

cmp 169
rjnz 3
mov8 b 1
cmp 230
rjnz 3
mov8 b 3
cmp 227
rjnz 3
mov8 b 5
cmp 228
rjnz 3
mov8 b 9
cmp 235
rjnz 3
mov8 b 11
cmp 162
rjnz 3
mov8 b 13
cmp 239
rjnz 3
mov8 b 17
cmp 231
rjnz 3
mov8 b 19
cmp 225
rjnz 3
mov8 b 21

add c b

ld a state
cmp 0
mov8 a 1
mov8 b *x
rjz 5
mov8 a 0
mov8 b *o
wr a state

wr b c
ret



lbl_draw
mov b field
lbl_suka
ld a b
inc b
cmp 255
jz ext
putc
jmp suka
lbl_ext
ret


lbl_field
124 32 124 32 124 32 124 10
124 32 124 32 124 32 124 10
124 32 124 32 124 32 124 10
255

lbl_state
1

ret
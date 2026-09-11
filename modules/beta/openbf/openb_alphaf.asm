bf.run:
# interpreter here
mov a _bf.prog
ld b _bf.vars
add a b
inc b
wr b _bf.vars
ld a a
cmp '+'
jmp _bf.inc
cmp '.'
jz _bf.put
jmp bf.run
ret

_bf.inc:
mov a _bf.data
mov b _bf.vars
inc b
ld b b
add a b
ld a a
inc a
mov c _bf.data
add b c
wr a b
jmp bf.run
ret

_bf.put:
mov a _bf.data
mov b _bf.vars
inc b
ld b b
add a b
ld a a
ld a a
putc
jmp bf.run


_bf.vars:
0 0 0 0
# pc, dc, nn, nn

_bf.data:
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
# 64 bytes of data memory

_bf.prog:
"+++++++++++.+.+.+.+."+
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
# 256 bytes of prog memory

bf.input:
exch
mov c 64
mov b _bf.data
inc c
_bf.gloop:
dec c
mov a c
cmp 0
jz _bf.gexit
getkey
cmp 13
jz _bf.gexit
putc
wr a b
inc b
jmp _bf.gloop
_bf.gexit:
endl
mov8 a 0
wr a b
exch
ret
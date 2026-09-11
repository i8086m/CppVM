call bf.run
ret


bf.run:
# init here
nop
_bf.loop:
mov a _bf.prog
add a c
inc c
ld a a
# dbg
#putc
#endl
# dbg
cmp 43
jz _bf.inc
cmp 45
jz _bf.dec
#cmp 60
#jz _bf.left
#cmp 62
#jz _bf.right
#cmp 44
#jz _bf.get
cmp 46
jz _bf.put
#cmp 91
#jz _bf.sol
#cmp 93
#jz _bf.eol
cmp 0
jz _bf.exit
jmp _bf.loop
_bf.exit:
ret

_bf.inc:
mov a _bf.data
ld b _bf.dc
add b a
ld a b
inc a
wr a b
jmp _bf.loop

_bf.dec:
mov a _bf.data
ld b _bf.dc
add b a
ld a b
dec a
wr a b
jmp _bf.loop


_bf.put:
mov a _bf.data
ld b _bf.dc
add b a
ld a b
putc
jmp _bf.loop

# pc was here
_bf.dc: 0
_bf.br: 0

_bf.data:
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
# 64 bytes of data memory

_bf.prog:
"s+++++++++++++++++++++++++++++++++++++++++++++"+
"s+++++++++++++++++++++++++++.+++++++++++++++++"+
"s++++++++++++.+++++++..+++.-------------------"+
"s---------------------------------------------"+
"s---------------.+++++++++++++++++++++++++++++"+
"s++++++++++++++++++++++++++.++++++++++++++++++"+
"s++++++.+++.------.--------.------------------"+
"s---------------------------------------------"+
"s----.-----------------------."

bf.input:
mov a 103
put
endl
ret
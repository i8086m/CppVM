system:
mov b a
_sloop:
ld a b
cmp 0
jz _sexit
out
inc b
jmp _sloop
_sexit:
do
ret
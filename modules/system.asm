system:
wipe
mov b a
_sys.loop:
ld a b
cmp 0
jz _sys.exit
out
inc b
jmp _sys.loop
_sys.exit:
300
ret

system.sound:
mov a 7
putc
ret

system.color:
mov c a
mov b _system.colorstr
wipe
_sys.color.loop:
ld a b
cmp 0
jz _sys.color.exit
out
inc b
jmp _sys.color.loop
_sys.color.exit:
mov a c
out
300
ret

_system.colorstr:
"color "
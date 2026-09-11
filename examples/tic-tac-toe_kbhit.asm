main:
cls
call draw
call mark
jmp main


mark:
mov c field
kbhit

cmp 113
mov b 1
jz redraw
cmp 119
mov b 3
jz redraw
cmp 101
mov b 5
jz redraw
cmp 97
mov b 9
jz redraw
cmp 115
mov b 11
jz redraw
cmp 100
mov b 13
jz redraw
cmp 122
mov b 17
jz redraw
cmp 120
mov b 19
jz redraw
cmp 99
mov b 21
jz redraw
jmp mark

redraw:
add c b

ld a state
cmp 0
mov a 1
mov b "o"
rjz 5
mov a 0
mov b "x"
wr a state

wr b c
ret


draw:
mov b field
xloop:
ld a b
inc b
cmp 255
jz ext
putc
jmp xloop
ext:
ret


field:
"| | | |"
10
"| | | |"
10
"| | | |"
255

state:
1

ret
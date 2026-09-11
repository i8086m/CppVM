import modules/strings.asm

cls
mov a string
call putstr
getkey
ret

string:
"Hello World!\0"
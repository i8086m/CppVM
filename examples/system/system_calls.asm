import modules/system.asm

mov a "c"
call system.color

mov a command
call system

ret

command: "echo Hello World!\0"
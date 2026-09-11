import strings
_os_boot:
jmp _os_start

_str_os_info:
"cvmOS Kernel v0.0.1"+
10 10 0
_str_os_com:
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
_str_os_prefix:
"user@cvmOS:~$ "
_str_os_wrong:
"shell: no such command found"+
10 10 0
_str_os_cd:
"boot.cvm boot.asm test.txt"+
10 10 0


_os_start:
cls
mov a _str_os_info
call putstr

_os_console:
mov a _str_os_prefix
call putstr
mov a _str_os_com
mov8 b 20
call getstr
jmp _os_run
jmp _os_console


_os_run:
ld a _str_os_com
mov8 b 'c'
cmp b
jz _os_com_cd
jmp _os_nocom

_os_nocom:
mov a _str_os_wrong
call putstr
jmp _os_console

_os_com_cd:
mov a _str_os_cd
call putstr
jmp _os_console

ret
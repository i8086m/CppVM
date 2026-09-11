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
	"Hello\, world! "+
	"Privet\, mir!"


exit:
	noinf
	cin
	ret
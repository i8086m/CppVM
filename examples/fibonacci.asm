mov b 1
mov c 1
loop:

	add b c
	ld a count
	put
	inc a
	wr a count
	mov a 9
	putc
	mov a c
	put
	endl
	
	add c b
	ld a count
	put
	inc a
	wr a count
	mov a 9
	putc
	mov a b
	put
	endl
	cmp 1900000000

jn loop

count: 2
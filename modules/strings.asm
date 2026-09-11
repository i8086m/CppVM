; putstr(a)
; выводит строку до '\0'
; a - адрес строки
putstr:
mov b a
_ploop:
ld a b
cmp 0
jz _pexit
putc
inc b
jmp _ploop
_pexit:
ret


; getstr(a,b)
; Записывает введённую строку
; a - адрес строки
; b - макс. длина строки
getstr:
mov c b
mov b a
inc c
_gloop:
dec c
mov a c
cmp 0
jz _gexit
getkey
cmp 13
jz _gexit
putc
wr a b
inc b
jmp _gloop
_gexit:
endl
mov a 0
wr a b
ret

; TODO:
; cpystr(a,b)
; cmpstr(a,b)
; isdigit(a)
; getword
; alloc (memory.asm?)

; cmpstr(a,b)
; сравнивает строки по адресам a и b
cmpstr:
	wr a _strings_addr0
	wr b _strings_addr1
	ld b _strings_addr0
	mov c 0
	_lenchk0:
		ld a b
		cmp 0
		inc c
		inc b
		jnz _lenchk0
	push c
	ld b _strings_addr1
	mov c 0
	_lenchk1:
		ld a b
		cmp 0
		inc c
		inc b
		jnz _lenchk1
	mov a c
	pop b
	cmp b
	jz _cmp_step2
	mov a 0
ret

_cmp_step2:
	dec a
	mov c 0	; counter
	_cmp_loop2:
		ld a _strings_addr0
		ld b _strings_addr1
		add a c
		add b c
		inc c
		ld a a
		ld b b
		cmp b
		jnz _cmp_exit0
		cmp 0
		jnz _cmp_loop2
	mov a 1
ret

_cmp_exit0:
	mov a 0
	; endl put put put
	ret
ret

_strings_addr0: 0
_strings_addr1: 0
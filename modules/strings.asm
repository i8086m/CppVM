
# putstr(a)
# выводит строку до '\0'
# a - адрес строки
lbl_putstr
mov b a
lbl__ploop
ld a b
cmp 0
jz _pexit
putc
inc b
jmp _ploop
lbl__pexit
ret


# getstr(a,b)
# Записывает введённую строку
# a - адрес строки
# b - макс. длина строки
lbl_getstr
mov c b
mov b a
inc c
lbl__gloop
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
lbl__gexit
endl
#inc b
mov8 a 0
wr a b
ret


# cpystr(a,b)
# cmpstr(a,b)
# getstr(a)
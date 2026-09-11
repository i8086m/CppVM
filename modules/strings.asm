define putstring as call putstr
define getstring as call getstr


# putstr(a)
# выводит строку до '\0'
# a - адрес строки
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


# getstr(a,b)
# Записывает введённую строку
# a - адрес строки
# b - макс. длина строки
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
#inc b
mov8 a 0
wr a b
ret

# TODO:
# cpystr(a,b)
# cmpstr(a,b)
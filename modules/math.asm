; pow(a,b)
; Возводит число в степень
; a - число
; b - степень
pow:
mov c a
mov a b
mov b c
_math.a:
dec a
cmp 0
jz _math.b
mul b c
jmp _math.a
_math.b:
mov a b
ret

;a = 2
;b = 10
;c = 10
npow:
mov c a
mov a b
mov b c
inc a
_math.c:
dec a
cmp 0
jz _math.d
div b c
jmp _math.c
_math.d:
mov a b
ret


; mod(a)
; Возвращает модуль числа
; a - число
mod:
cmp 0
jn _math.tst
ret
_math.tst:
mov b a
sub a b
nop
sub a b
ret
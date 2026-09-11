
# pow(a,b)
# Возводит число в степень
# a - число
# b - степень
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

# mod(a)
# Возвращает модуль числа
# a - число
mod:
cmp 0
jn tst
ret
tst:
mov b a
sub a b
sub a b
ret
#
#
#
double.put:
mov b a
div a 10
put
mov a b
double_a:
cmp 10
jn double_e
sub a 10
jmp double_a
double_e:
mov b a
mov8 a '.'
putc
mov a b
put
ret



double.mul:
mov c b
cmp 0
jz double_mul_exit
dec a
add b c
double_mul_exit:
mov a b
ret


double.div:
div b 10
div a b
ret
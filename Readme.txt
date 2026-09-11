Программы храняться в файле bios.cvm (в той же директории что и CppVM.exe)


Планы:
- Проверить команды 190-194 на разрядность
- написать модуль float.asm
- использованная память в сообщении
- аргументы командной строки
- функции compstr, startswith, copystr
- выключить автоотправку строки
- нормальные строки ("hello" + 10 + "world!") (попробовать посимвольную обработку)
- определение функций (function sin a,b,c)
- исправить noinf (обрабатывать как команду, а не как флаг)
- exch (a, b, c)
- битовые сдвиги
- доделать openbf
- прерывания
- перевод исполняемых файлов в HEX-формат
- getch без заморозки потока (kbhit())
- графика (SFML)


Команды:

0 - nop
1 - inc a
2 - inc b
3 - inc c
4 - dec a
5 - dec b
6 - dec c
7 - cmp [double]
8 - cmp b
9 - cmp c

10 - put
11 - puts
12 - putc
13 - endl
14 - cin
15 - getkey
16 - cls
17 - rst
18 - exch
19 - call

20 - jmp [double]
21 - jz  [double]
22 - jnz [double]
23 - jn  [double]
24 - jp  [double]
25 - jmp c
26 - jz  c
27 - jnz c
28 - jn  c
29 - jp  c


30 - mov a b
31 - mov a c
32 - mov b a
33 - mov b c
34 - mov c a
35 - mov c b

40 - mov8 a [int]
41 - mov8 b [int]
42 - mov8 c [int]
43 - mov  a [double]
44 - mov  b [double]
45 - mov  c [double]


50 - ld a (addr)
51 - ld b (addr)
52 - ld c (addr)
53 - wr a (addr)
54 - wr b (addr)
55 - wr c (addr)

60 - ld a (a)
61 - ld a (b)
62 - ld a (c)
63 - ld b (a)
64 - ld b (b)
65 - ld b (c)
66 - ld c (a)
67 - ld c (b)
68 - ld c (c)

70 - wr a (a)
71 - wr a (b)
72 - wr a (c)
73 - wr b (a)
74 - wr b (b)
75 - wr b (c)
76 - wr c (a)
77 - wr c (b)
78 - wr c (c)

100 - setpos

110 - add a b
111 - add a c
112 - add b a
113 - add b c
114 - add c a
115 - add c b
116 - add a [int]
117 - add b [int]
118 - add c [int]

120 - sub a b
121 - sub a c
122 - sub b a
123 - sub b c
124 - sub c a
125 - sub c b
126 - sub a [int]
127 - sub b [int]
128 - sub c [int]

130 - mul a b
131 - mul a c
132 - mul b a
133 - mul b c
134 - mul c a
135 - mul c b
136 - mul a [int]
137 - mul b [int]
138 - mul c [int]

140 - div a b
141 - div a c
142 - div b a
143 - div b c
144 - div c a
145 - div c b
146 - div a [int]
147 - div b [int]
148 - div c [int]

150 - and [double]
151 - or  [double]
152 - xor [double]
153 - not a
154 - and b
155 - or  b
156 - xor b

160 - in
161 - out
162 - wipe
163 - do

190 - rjmp [signed]
191 - rjz  [signed]
192 - rjnz [signed]
193 - rjn  [signed]
194 - rjp  [signed]

250 - noinf (Отключено)
251 - debug (Отключено)
255 - ret


Директивы ассемблера:

import NAME - импорт модуля modules/NAME.asm
#комментарий - для описания работы программы
label: - метка
'a' - символ
"abcde" - строка
"abcde"+ - строка без терминатора
%10110 - двочиное число
-43 - отрицательное число
define x as y - заменять все X на Y
message x - вывод сообщения при сборке
warning x - вывод предупреждения при сборке

Справка по файлам:

bios.asm - Исходный файл
bios.cvm - Исполняемый файл
modules/ - папка с модулями
examples/ - папка с примерами
asm.py - ассемблер
mide.py - среда разработки
cppvm.exe - виртуальная машина
readme.txt - информация о сборке

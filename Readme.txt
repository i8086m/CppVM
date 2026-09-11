CppVM v2.0 Final от 2018.12.01

Программы храняться в файле bios.cvm (в той же директории что и CppVM.exe)

Изменения:

2018.12.01 [2.1.0]: Начало разработки 2.1
2018.12.01 [2.0.0]: Статус "Final"
2018.11.29 [2.0.0]: Правки


Планы:

* Классический формат комментариев (;) [2.1]
* Графика [SFML/WinAPI, 2.1]
* Команды зависящие от платформы [2.1]
* Идентификатор платформы [2.1]
* head COMMAND для ассемблера [2.1]
* Добавить getch без заморозки потока (kbhit()) [2.1]

* Функции compstr, startswith, copystr [2.2]
* Исправить побитовые команды и RJMP'ы [2.2]
* Запретить доступ к несуществующим ячейкам через RAMSIZE [2.2]
* Изменяемый RAMSIZE (Для расширения памяти на cvm/arduino) [2.2]

* Выбор файла для сборки [2.3]
* Работа с файлами [2.3]
* Аргументы командной строки [2.3]
* Две директивы define идущих подряд ломают программу [2.3]

* Прерывания [2.4]
* Расширение набора регистров [2.4]
* Отдельный exch для каждого регистра [2.4]
* Битовые сдвиги [2.4]

* Ввод с клавиатуры для openbf
* Проверить все команды и директивы
* Модуль float.asm
* Нормальные строки ("hello" + 32 + "world!") (попробовать посимвольную обработку)
* Перевод исполняемых файлов в HEX-формат
* Компилятор

Команды:

command:		status:
0 - nop			OK
1 - inc a		OK
2 - inc b		OK
3 - inc c		OK
4 - dec a		OK
5 - dec b		OK
6 - dec c		OK
7 - cmp [32]		OK
8 - cmp b		OK
9 - cmp c		OK

10 - put		OK
11 - puts		OK
12 - putc		OK
13 - endl		OK
14 - cin		OK
15 - getkey		OK
16 - cls		OK
17 - rst		OK
18 - exch		OK
19 - call

20 - jmp [32]		OK
21 - jz  [32]		OK
22 - jnz [32]		OK
23 - jn  [32]		OK
24 - jp  [32]		OK
25 - jmp c		OK
26 - jz  c		OK
27 - jnz c		OK
28 - jn  c		OK
29 - jp  c		OK


30 - mov a b		OK
31 - mov a c		OK
32 - mov b a		OK
33 - mov b c		OK
34 - mov c a		OK
35 - mov c b		OK

40 - mov8 a [16]	supressed
41 - mov8 b [16]	supressed
42 - mov8 c [16]	supressed
43 - mov  a [32]	OK
44 - mov  b [32]	OK
45 - mov  c [32]	OK


50 - ld a (32)
51 - ld b (32)
52 - ld c (32)
53 - wr a (32)
54 - wr b (32)
55 - wr c (32)

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
116 - add a [32]
117 - add b [32]
118 - add c [32]

120 - sub a b
121 - sub a c
122 - sub b a
123 - sub b c
124 - sub c a
125 - sub c b
126 - sub a [32]
127 - sub b [32]
128 - sub c [32]

130 - mul a b
131 - mul a c
132 - mul b a
133 - mul b c
134 - mul c a
135 - mul c b
136 - mul a [32]
137 - mul b [32]
138 - mul c [32]

140 - div a b
141 - div a c
142 - div b a
143 - div b c
144 - div c a
145 - div c b
146 - div a [32]
147 - div b [32]
148 - div c [32]

150 - and [32]	BROKEN
151 - or  [32]
152 - xor [32]
153 - not a
154 - and b
155 - or  b
156 - xor b

160 - in
161 - out
162 - wipe
163 - do

190 - rjmp [signed]	BROKEN?
191 - rjz  [signed]
192 - rjnz [signed]
193 - rjn  [signed]
194 - rjp  [signed]

250 - inf
251 - debug
252 - nodebug
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
function_name(a, b) - вызов функции
function function_name 2 - создание функции

Справка по файлам:

bios.asm - Исходный файл
bios.cvm - Исполняемый файл
modules/ - папка с модулями
examples/ - папка с примерами
asm.py - ассемблер
mide.py - среда разработки
cppvm.exe - виртуальная машина
readme.txt - информация о сборке
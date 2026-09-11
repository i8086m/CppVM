CppVM v2.2 Final от 2018.12.30

Программы храняться в файле bios.cvm (в той же директории что и CppVM.exe)

Изменения:

2018.12.30 [2.2.0]: Статус "Final"
2018.12.30 [2.2.0]: ASMpy полностью заменён на CVA X
2018.12.24 [2.2.0]: Команда с кодом 17 заменена на call c
2018.12.24 [2.2.0]: Начало разработки CVA X
2018.12.29 [2.1.0]: Статус "Final"
2018.12.01 [2.1.0]: Добавлена директива header <asm>
2018.12.01 [2.1.0]: Добавлены "классические" комментарии (;comment)
2018.12.01 [2.1.0]: Добавлен пример "graphics"
2018.12.01 [2.1.0]: Создан модуль windows
2018.12.01 [2.1.0]: Добавлены графические команды
2018.12.01 [2.1.0]: Изменены коды команд setpos и system
2018.12.01 [2.1.0]: Добавлена возможность выбрать исходный файл
2018.12.01 [2.1.0]: Некоторые файлы были перемещены
2018.12.01 [2.1.0]: Начало разработки 2.1
2018.12.01 [2.0.0]: Статус "Final"
2018.11.29 [2.0.0]: Правки


Планы:

* Пользовательские команды (Функции 2.0) [2.3]
* Добавить getch без заморозки потока (kbhit()) [2.3]
* Аргументы командной строки [2.3]
* Изменяемый RAMSIZE (через аргументы) [2.3]
* Битовые сдвиги [2.3]

* Набор команд SFML [2.4]
* Работа с файлами [2.4]
* Перевод исполняемых файлов в BIN-формат [2.4]

* Проверить все команды и директивы [LTS 2 | 2.5]
* Запретить доступ к несуществующим ячейкам через RAMSIZE [LTS 2 | 2.5]
* Убрать глобальное i++ и заменить на i++ и continue для каждой команды [LTS 2 | 2.5]

* Прерывания
* Функции compstr, startswith, copystr
* Поддержка разной разрядности
* Модуль float.asm


Команды:

0 - nop
1 - inc a
2 - inc b
3 - inc c
4 - dec a
5 - dec b
6 - dec c
7 - cmp [32]
8 - cmp b
9 - cmp c

10 - put
11 - puts
12 - putc
13 - endl
14 - cin
15 - getkey
16 - cls
17 - call c
18 - exch
19 - call (32)

20 - jmp [32]
21 - jz  [32]
22 - jnz [32]
23 - jn  [32]
24 - jp  [32]
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

40 - СВОБОДНО
41 - СВОБОДНО
42 - СВОБОДНО
43 - mov  a [32]
44 - mov  b [32]
45 - mov  c [32]


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

150 - and [32]		OPCODE ONLY
151 - or  [32]		OPCODE ONLY
152 - xor [32]		OPCODE ONLY
153 - not a		OPCODE ONLY
154 - and b		OPCODE ONLY
155 - or b		OPCODE ONLY
156 - xor b		OPCODE ONLY

160 - pop
161 - push
162 - wipe
163

190 - rjmp [signed]
191 - rjz  [signed]
192 - rjnz [signed]
193 - rjn  [signed]
194 - rjp  [signed]

250 - inf
251 - debug
252 - nodebug
255 - ret

300 - do		OPCODE ONLY
301 - setpos		OPCODE ONLY


Директивы ассемблера:

label: - метка
; комментарий - для описания работы программы
-43 - отрицательное число
"abcde" - строка
"abcde\0" - строка с терминатором
import folder/file.asm - импорт модуля folder/file.asm
header x - перенести строку в начало программы


Справка по файлам:

*.asm - исходные файлы
bios.cvm - исполняемый файл
modules/ - папка с модулями
examples/ - папка с примерами
other/ - разные файлы
asm.exe - ассемблер
cppvm.exe - виртуальная машина
readme.txt - информация о сборке
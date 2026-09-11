Программы храняться в файле bios.cvm (в той же директории что и CppVM.exe)
Если нет программы или программа выполнена, запускается MiniIDE

Минусы:
- Нет многих необходимых комманд
- Память ограничена 256 байтами

Команды:

0 - nop
1 - inc a
2 - inc b
3 - inc c
4 - dec a
5 - dec b
6 - dec c
7 - cmp a,[int]
8 - cmp b,[int]
9 - cmp c,[int]

10 - cout
11 - couts
12 - cnl
13 - cin
14 - getch
15 - cls

20 - rst
21 - jmp [int]
22 - jz [int]
23 - jnz [int]
24 - jn [int]
25 - jp [int]

30 - mov a,b
31 - mov a,c
32 - mov b,a
33 - mov b,c
34 - mov c,a
35 - mov c,b

40 - mov a,[int]
41 - mov b,[int]
42 - mov c,[int]

50 - mov a,[addr]
51 - mov b,[addr]
52 - mov c,[addr]
53 - mov [addr],a
54 - mov [addr],b
55 - mov [addr],c

60 - add a,b
61 - add a,c
62 - add b,a
63 - add b,c
64 - add c,a
65 - add c,b
66 - add a,[int]
67 - add b,[int]
68 - add c,[int]

70 - sub a,b
71 - sub a,c
72 - sub b,a
73 - sub b,c
74 - sub c,a
75 - sub c,b
76 - sub a,[int]
77 - sub b,[int]
78 - sub c,[int]

80 - mul a,b
81 - mul a,c
82 - mul b,a
83 - mul b,c
84 - mul c,a
85 - mul c,b
86 - mul a,[int]
87 - mul b,[int]
88 - mul c,[int]

90 - div a,b
91 - div a,c
92 - div b,a
93 - div b,c
94 - div c,a
95 - div c,b
96 - div a,[int]
97 - div b,[int]
98 - div c,[int]


250 - endf
251 - idef
255 - ret
Программы храняться в файле bios.cvm (в той же директории что и CppVM.exe)
Если нет программы или программа выполнена, запускается MiniIDE


Ошибки:
- Не устанавливаются флаги при вычислении (решение - использовать cmp)
- ? Ассемблер не поддерживает комманды 30-39
- Серьезные ошибки ассемблера

Команды:

0 - nop
1 - inc a
2 - inc b
3 - inc c
4 - dec a
5 - dec b
6 - dec c
7 - cmp [int]
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
18 - ex
19 - call

20 - jmp [addrH],[addrL]
21 - jz  [addrH],[addrL]
22 - jnz [addrH],[addrL]
23 - jn  [addrH],[addrL]
24 - jp  [addrH],[addrL]
25 - jmp bc
26 - jz  bc
27 - jnz bc
28 - jn  bc
29 - jp  bc


30 - rjmp [signed]
31 - rjz  [signed]
32 - rjnz [signed]
33 - rjn  [signed]
34 - rjp  [signed]
35 - rjmp c
36 - rjz  c
37 - rjnz c
38 - rjn  c
39 - rjp  c

40 - mov a,b
41 - mov a,c
42 - mov b,a
43 - mov b,c
44 - mov c,a
45 - mov c,b
46 - mov a,[int]
47 - mov b,[int]
48 - mov c,[int]

50 - ld a,(addr)
51 - ld b,(addr)
52 - ld c,(addr)
53 - wr a,(addr)
54 - wr b,(addr)
55 - wr c,(addr)
56 - ld a,(bc)
57 - wr (a), bc
58 - ld bc,[double]

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


250 - dbg
251 - ide
255 - ret

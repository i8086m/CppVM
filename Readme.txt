
    	 W E L C O M E   T O

█████ ██████ ██████ ██     ██ ██    ██
█████ ██  ██ ██  ██  ██   ██  ███  ███
██    ██  ██ ██  ██  ██   ██  ████████
██    ██████ ██████   ██ ██   ██ ██ ██
█████ ██     ██       ██ ██   ██    ██
█████ ██     ██        ███    ██    ██

-- designed and programmed by i8086m --


Executables:
	* cvm.exe — the c plus plus virtual machine. Executes *.cvm files
	* asm.exe — the cvm assember. Converts *.asm files to *.cvm


TODO List:
	* Add CLI args to select files
	* Verify jump command implementation and remove magic numbers
	* Check RAM_SIZE OOB on RAM access
	* Warn/halt on stack/ustack overflow
	* Use binary format for bytecode files`
	* File I/O
	* Interrupts
	* copystr and startswith functions
	* Floating point support module
	* Interface for calling native code
	* A compiler (eventually)


Supported assembler directives:
	* Labels                myLabel:
	* Comments              ; a comment
	* Negative numbers      -43 - negative numbers
	* Strings               "abcde" - strings
	* Terminated strings    "abcde\0" - terminated strings
	* Module imports        import folder/file.asm
	* Move to file header   header some_code_line
	* Define a function     def myFunc N
	* Call a function       myFunc A B C


Opcode list:

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
21 - jz  [32] // a == b; z
22 - jnz [32] // a != b; !z
23 - jl  [32] // a < b; c
24 - jg  [32] // a > b; !c && !z
25 - jmp c
26 - jz  c
27 - jnz c
28 - jl  c
29 - jb  c


30 - mov a b
31 - mov a c
32 - mov b a
33 - mov b c
34 - mov c a
35 - mov c b


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
146 - div a [int]
147 - div b [int]
148 - div c [int]

150 - and [int]	    (Not implemented in the assembler yet, sorry)
151 - or  [int]	    (Not implemented in the assembler yet, sorry)
152 - xor [int]	    (Not implemented in the assembler yet, sorry)
153 - not a		    (Not implemented in the assembler yet, sorry)
154 - and b		    (Not implemented in the assembler yet, sorry)
155 - or b		    (Not implemented in the assembler yet, sorry)
156 - xor b		    (Not implemented in the assembler yet, sorry)

160 - wipe
161 - push a
162 - push b
163 - push c
164 - pop a
165 - pop b
166 - pop c
167 - push [32]

170 - kbhit

180 - pushif z
181 - pushif nz
182 - pushif l
183 - pushif g

190 - rjmp [signed]
191 - rjz  [signed]
192 - rjnz [signed]
193 - rjl  [signed]
194 - rjg  [signed]

250 - inf
255 - ret

300 - do		    (Extended opcode, not implemented in the assembler)
301 - setpos		(Extended opcode, not implemented in the assembler)




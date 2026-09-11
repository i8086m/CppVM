f_out = open('bios.asm', 'w')
src = '>+>++>+++.<.<.<.>.>.>.'

out = '''inf
jmp _start

# Build by OpenBF Project

_mem:
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0

_start:
'''

# b - pc

abyss = 0

for i in src:
	if i == '>':
		out+='\ninc b'
	elif i == '<':
		out+='\ndec b'
	elif i == '+':
		out+='\nmov c _mem\nadd c b\nld a c\ninc a\nwr a c'
	elif i == '-':
		out+='\nmov c _mem\nadd c b\nld a c\ndec a\nwr a c'
	elif i == '.':
		out+='\nmov c _mem\nadd c b\nld a c\nput'
out+='\nret'
		
f_out.write(out)
f_out.close()
print(out)
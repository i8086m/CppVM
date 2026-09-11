f_out = open('bios.asm', 'w')

try:
	f_in = open('bios.bf')
except:
	print('no source file')
	f_out.close()
	exit()
src = f_in.read()

out = '''inf
jmp _start

# Build by OpenBF Project

_mem:
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
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
		out+='\nmov c _mem\nadd c b\nld a c\nputc'
	elif i == ',':
		out+='\n#UNSUPPORTED'
	elif i == '[':
		abyss+=1
		out+='\n_jp'+str(abyss)+':\ncmp 0\njz _jp'+str(abyss)+'a'
	elif i == ']':
		out+='\njmp _jp'+str(abyss)+'\n_jp'+str(abyss)+'a:'
		abyss-=1
	else:
		out+=i
out+='\nret'
		
f_out.write(out)
f_out.close()
print(out)
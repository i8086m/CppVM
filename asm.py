print('Opening files...')
f_out = open('bios.cvm', 'w')

try:
	f_in = open('bios.asm')
except:
	print('\n-----------------------------------------------')
	print('Assemble failed. Source file not found')
	print('-----------------------------------------------\n')
	cvm = '255\nAssemble Failed\nerr: unableToFindSource(bios.asm)'
	f_out.write(cvm)
	f_out.close()
	exit()

labels = []
lbln = []
lbli = []
errors = ''
cvm = ''
print('Reading...')
asm = f_in.read()

print('Collecting modules...')
coms = asm.split('\n')
for i in coms:
	if (str(i).startswith('import ')):
		asm = asm.replace(i,'')
		i = str(i)[7:]
		i = 'modules/'+i+'.asm'
		try:
			mod_in = open(i)
			mod_dat = mod_in.read()
			asm = asm + '\n' + mod_dat
		except:
			print('\n---------------------------------------------------------')
			print('Assemble failed. Module ' + i + ' is not installed')
			print('---------------------------------------------------------\n')
			cvm = '255\nAssemble Failed\nerr: unableToFindModule(' + i + ')'
			f_out.write(cvm)
			f_out.close()
			exit()

print('Preparing...')
asm = asm + ' '
asm = asm.replace('\t','')
asm = asm.replace('{','')
asm = asm.replace('}','ret')

print('Preprocessing...')
coms = asm.split('\n')
for i in coms:
	if (str(i).startswith('define ')):
		try:
			a = i[7:]
			a = a.split(' as ')
			asm = asm.replace(i,'')
			asm = asm.replace(' '+a[0]+' ',' '+(a[1].replace('\\n','\n'))+' ')
			asm = asm.replace('\n'+a[0]+' ','\n'+(a[1].replace('\\n','\n'))+' ')
			asm = asm.replace(' '+a[0]+'\n',' '+(a[1].replace('\\n','\n'))+'\n')
			asm = asm.replace('\n'+a[0]+'\n','\n'+(a[1].replace('\\n','\n'))+'\n')
		except:
			print('define error')
	if (str(i).startswith('message ')):
		asm = asm.replace(i,'')
		print(str(i[8:]))
	if (str(i).startswith('warning ')):
		asm = asm.replace(i,'')
		print()
		print(' Warning: '+str((i[8:])))
		print()
		input()

coms = asm.split('\n')
funcs = []
for i in coms:
	if (i.startswith('function')):
		a = i.split(' ')
		b=''
		for x in range(int(a[2])):
			b+= str(a[1])+'_var'+str(x)+': 0\n'
		b+=str(a[1])+':'
		funcs.append(str(a[1]))
		asm = asm.replace(i, b)

for i in coms:
	for x in funcs:
		if (x in i):
			b = i.lstrip(str(x))
			if (b.startswith('(') and b.endswith(')')):
				b=b[1:-1].replace(' ','').split(',')
				c=''
				for ind, d in enumerate(b):
					if (d!=''):
						c+= 'mov c ' + b[ind] + '\nwr c '+str(x)+'_var'+str(ind)+'\n'
				c+='call '+str(x)+'\n'
				asm = asm.replace(i,c)

print('Removing comments...')
coms = asm.split('\n')
for i in coms:
	if (str(i).startswith('#')):
		asm = asm.replace(str(i),'')

print('Converting strings...')
coms = asm.split('\n')
for i in coms:
	if (str(i).startswith('"')):
			c = i[1:]
			c = c.strip()
			if (str(c).endswith('"')):
				c = c.replace('"','')
			if (str(c).endswith('" +')):
				c = c.replace('" +','')
			if (str(c).endswith('"+')):
				c = c.replace('"+','')
			b = ''
			for a in c:
					b = b + str(ord(a))
					b = b + ' '
			if (str(i).endswith('" +') or str(i).endswith('"+')):
					pass
			else:
					b = b + '0'
			asm = asm.replace(i,b)

print('Converting chars...')
coms = asm.replace('\n',' ')
coms = coms.split(' ')
for ind, i in enumerate(coms):
	if (str(i).startswith("'") and str(i).endswith("'")):
		try:
			a = i[1:]
			a = a[:1]
			a = ord(a)
			asm = asm.replace(str(i),str(a))
		except:
			pass

print('Splitting 16-bit numbers...')
coms = asm.replace('\n',' ')
coms = coms.split(' ')
out = list(filter(None, coms))
lbln = []
for ind, com in enumerate(coms):
	if com.endswith(':'):
		lbln.append(str(com.replace(':','')))
coms = asm.split('\n')
doubleints = ['cmp ','mov ','jmp ','jz ','jnz ','jn ','jp ','and ','or ','xor ','ld ','wr ']
for ind, i in enumerate(coms):
	for a in doubleints:
		if (i.startswith(a)):
			b = i.replace(a,'')
			d = ''
			x = 0
			for f in lbln:
				if f in b:
					x = 1
			if (x == 0):
				for c in b:
					if (c in '-1234567890'):
						d = d + c
				if (d):
					e = str(int(d)//256) + ' ' + str(int(d)%256)
					asm = asm.replace(i+'\n',i.replace(d,e)+'\n')

print('Assembling...')
doCount = 2
while (doCount > 0):
	doCount-=1
	asm = asm.lower()
	asm = asm.replace('  ',' ')
	asm = asm.replace('\',\'','zap')
	asm = asm.replace(', ',' ')
	asm = asm.replace(',',' ')
	asm = asm.replace('zap','\',\'')
	asm = asm.replace('\' \'','32')
	asm = asm.replace('\'\\r\'','13')
	asm = asm.replace('\'\\n\'','10')
	asm = asm.replace('\'\\t\'','9')
	asm = asm.replace('\'\\0\'','0')
	asm = ' ' + asm
	asm = asm.replace('\n',' ')
	asm = asm.replace(' nop ',' 0 ')
	asm = asm.replace(' nop ',' 0 ')
	asm = asm.replace(' inc a ',' 1 ')
	asm = asm.replace(' inc b ',' 2 ')
	asm = asm.replace(' inc c ',' 3 ')
	asm = asm.replace(' dec a ',' 4 ')
	asm = asm.replace(' dec b ',' 5 ')
	asm = asm.replace(' dec c ',' 6 ')
	asm = asm.replace(' cmp b ',' 8 ')
	asm = asm.replace(' cmp c ',' 9 ')
	asm = asm.replace(' cmp ',' 7 ')

	asm = asm.replace(' puts ',' 11 ')
	asm = asm.replace(' putc ',' 12 ')
	asm = asm.replace(' put ',' 10 ')
	asm = asm.replace(' endl ',' 13 ')
	asm = asm.replace(' cin ',' 14 ')
	asm = asm.replace(' getkey ',' 15 ')
	asm = asm.replace(' cls ',' 16 ')
	asm = asm.replace(' rst ',' 17 ')
	asm = asm.replace(' exch ',' 18 ')
	asm = asm.replace(' call ',' 19 ')

	asm = asm.replace(' rjmp ',' 190 ')
	asm = asm.replace(' rjz ',' 191 ')
	asm = asm.replace(' rjnz ',' 192 ')
	asm = asm.replace(' rjn ',' 193 ')
	asm = asm.replace(' rjp ',' 194 ')

	asm = asm.replace(' jmp c ',' 25 ')
	asm = asm.replace(' jz c ',' 26 ')
	asm = asm.replace(' jnz c ',' 27 ')
	asm = asm.replace(' jn c ',' 28 ')
	asm = asm.replace(' jp c ',' 29 ')
	asm = asm.replace(' jmp ',' 20 ')
	asm = asm.replace(' jz ',' 21 ')
	asm = asm.replace(' jnz ',' 22 ')
	asm = asm.replace(' jn ',' 23 ')
	asm = asm.replace(' jp ',' 24 ')

	asm = asm.replace(' mov a b ',' 30 ')
	asm = asm.replace(' mov a c ',' 31 ')
	asm = asm.replace(' mov b a ',' 32 ')
	asm = asm.replace(' mov b c ',' 33 ')
	asm = asm.replace(' mov c a ',' 34 ')
	asm = asm.replace(' mov c b ',' 35 ')

	asm = asm.replace(' mov8 a ',' 40 ')
	asm = asm.replace(' mov8 b ',' 41 ')
	asm = asm.replace(' mov8 c ',' 42 ')
	asm = asm.replace(' mov a ',' 43 ')
	asm = asm.replace(' mov b ',' 44 ')
	asm = asm.replace(' mov c ',' 45 ')

	asm = asm.replace(' ld a a ',' 60 ')
	asm = asm.replace(' ld a b ',' 61 ')
	asm = asm.replace(' ld a c ',' 62 ')
	asm = asm.replace(' ld b a ',' 63 ')
	asm = asm.replace(' ld b b ',' 64 ')
	asm = asm.replace(' ld b c ',' 65 ')
	asm = asm.replace(' ld c a ',' 66 ')
	asm = asm.replace(' ld c b ',' 67 ')
	asm = asm.replace(' ld c c ',' 68 ')

	asm = asm.replace(' wr a a ',' 70 ')
	asm = asm.replace(' wr a b ',' 71 ')
	asm = asm.replace(' wr a c ',' 72 ')
	asm = asm.replace(' wr b a ',' 73 ')
	asm = asm.replace(' wr b b ',' 74 ')
	asm = asm.replace(' wr b c ',' 75 ')
	asm = asm.replace(' wr c a ',' 76 ')
	asm = asm.replace(' wr c b ',' 77 ')
	asm = asm.replace(' wr c c ',' 78 ')

	asm = asm.replace(' ld a ',' 50 ')
	asm = asm.replace(' ld b ',' 51 ')
	asm = asm.replace(' ld c ',' 52 ')
	asm = asm.replace(' wr a ',' 53 ')
	asm = asm.replace(' wr b ',' 54 ')
	asm = asm.replace(' wr c ',' 55 ')

	asm = asm.replace(' setpos ',' 100 ')

	asm = asm.replace(' add a b ',' 110 ')
	asm = asm.replace(' add a c ',' 111 ')
	asm = asm.replace(' add b a ',' 112 ')
	asm = asm.replace(' add b c ',' 113 ')
	asm = asm.replace(' add c a ',' 114 ')
	asm = asm.replace(' add c b ',' 115 ')
	asm = asm.replace(' add a ',' 116 ')
	asm = asm.replace(' add b ',' 117 ')
	asm = asm.replace(' add c ',' 118 ')

	asm = asm.replace(' sub a b ',' 120 ')
	asm = asm.replace(' sub a c ',' 121 ')
	asm = asm.replace(' sub b a ',' 122 ')
	asm = asm.replace(' sub b c ',' 123 ')
	asm = asm.replace(' sub c a ',' 124 ')
	asm = asm.replace(' sub c b ',' 125 ')
	asm = asm.replace(' sub a ',' 126 ')
	asm = asm.replace(' sub b ',' 127 ')
	asm = asm.replace(' sub c ',' 128 ')

	asm = asm.replace(' mul a b ',' 130 ')
	asm = asm.replace(' mul a c ',' 131 ')
	asm = asm.replace(' mul b a ',' 132 ')
	asm = asm.replace(' mul b c ',' 133 ')
	asm = asm.replace(' mul c a ',' 134 ')
	asm = asm.replace(' mul c b ',' 135 ')
	asm = asm.replace(' mul a ',' 136 ')
	asm = asm.replace(' mul b ',' 137 ')
	asm = asm.replace(' mul c ',' 138 ')

	asm = asm.replace(' div a b ',' 140 ')
	asm = asm.replace(' div a c ',' 141 ')
	asm = asm.replace(' div b a ',' 142 ')
	asm = asm.replace(' div b c ',' 143 ')
	asm = asm.replace(' div c a ',' 144 ')
	asm = asm.replace(' div c b ',' 145 ')
	asm = asm.replace(' div a ',' 146 ')
	asm = asm.replace(' div b ',' 147 ')
	asm = asm.replace(' div c ',' 148 ')

	asm = asm.replace(' and b ',' 154 ')
	asm = asm.replace(' or b ',' 155 ')
	asm = asm.replace(' xor b ',' 156 ')
	asm = asm.replace(' not a ',' 153 ')
	asm = asm.replace(' and ',' 150 ')
	asm = asm.replace(' or ',' 151 ')
	asm = asm.replace(' xor ',' 152 ')

	asm = asm.replace(' in ',' 160 ')
	asm = asm.replace(' out ',' 161 ')
	asm = asm.replace(' wipe ',' 162 ')
	asm = asm.replace(' do ',' 163 ')

	asm = asm.replace(' inf ',' 250 ')
	asm = asm.replace(' debug ',' 251 ')
	asm = asm.replace(' nodebug ',' 252 ')
	asm = asm.replace(' ret ',' 255 ')


print('Calculating labels...')
out = asm.split(' ')
out = list(filter(None, out))
lbln = []
lbli = []

for ind, com in enumerate(out): # запись в массив информации о метках (место, имя)
	if com.endswith(':'):
		lab = out[ind].replace(':','')
		lbln.append(str(lab))
		lbli.append(str(ind))
for ind, com in enumerate(out): # добавить второй байт к каждой метке
	for nam in lbln:
		if com == nam:
			out.insert(ind+1,'000')
lbln = []
lbli = []
for ind, com in enumerate(out): # удаление инициализаторов меток
	if com.endswith(':'):
		lab = out[ind].replace(':','')
		del out[ind]
		lbln.append(str(lab))
		lbli.append(str(ind))

for ind, nam in enumerate(lbln): # замена меток адресами
	for indc, com in enumerate(out):
		if (com == nam):
			out[indc] = str(list(divmod(int(lbli[ind]), 256))[0])
			out[indc+1] = str(list(divmod(int(lbli[ind]), 256))[1])

print('Converting numbers...')

for ind, i in enumerate(out): # отрицательные числа
	if (str(i).startswith('-')):
		a = i[1:]
		a = 256-int(a)
		out[ind] = a


for ind, i in enumerate(out): # двоичные числа
	if (str(i).startswith('%')):
		a = i[1:]
		a = int(a,2)
		out[ind] = a


for com in out:
	cvm = cvm + str(com) + ' '

print('Checking output...')
count = 0
for i in cvm:
	if i.isalpha() and not i == ' ':
		count += 1
		errors = errors + i


print('Coneverting...')
################
# Convert here #
################




if count != 0:
	print('\n-----------------------------------------------')
	print('Assemble failed. Unknown command: ' + errors)
	print('-----------------------------------------------\n')
	cvm = '255\nAssemble Failed\nerr: unknownCommand(' + errors + ')'
	f_out.write(cvm)
	f_out.close()
	exit()
else:
	print('\n---------------------')
	print('Assemble completed.')
	print('---------------------\n')


print('Writing...')
cvm = cvm.replace(' ','\n')
f_out.write(cvm)
f_out.close()

print('Done!')
#kek = input()

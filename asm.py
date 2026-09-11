print('Opening files...')
f_in = open('bios.asm')
f_out = open('bios.cvm', 'w')
labels = []
lbln = []
lbli = []
errors = ''
cvm = ''
print('Reading...')
asm = f_in.read()
print('Assembling...')

asm = asm.lower()
asm = asm.replace(' ',' ')
asm = asm.replace('  ',' ')
asm = asm.replace(', ',' ')
asm = asm.replace(',',' ')
asm = asm.replace('\n',' ')

asm = asm.replace('nop','0')
asm = asm.replace('inc a','1')
asm = asm.replace('inc b','2')
asm = asm.replace('inc c','3')
asm = asm.replace('dec a','4')
asm = asm.replace('dec b','5')
asm = asm.replace('dec c','6')
asm = asm.replace('cmp b','8')
asm = asm.replace('cmp c','9')
asm = asm.replace('cmp ','7 ')

asm = asm.replace('puts','11')
asm = asm.replace('putc','12')
asm = asm.replace('put','10')
asm = asm.replace('endl','13')
asm = asm.replace('cin','14')
asm = asm.replace('getkey','15')
asm = asm.replace('cls','16')
asm = asm.replace('rst','17')
asm = asm.replace('sde','18')
asm = asm.replace('call ','19 ')

asm = asm.replace('jmp bc','25')
asm = asm.replace('jz bc','26')
asm = asm.replace('jnz bc','27')
asm = asm.replace('jn bc','28')
asm = asm.replace('jp bc','29')
asm = asm.replace('jmp','20')
asm = asm.replace('jz','21')
asm = asm.replace('jnz','22')
asm = asm.replace('jn','23')
asm = asm.replace('jp','24')

############################
###   30-39 Missing!!!   ###
############################

asm = asm.replace('mov a b','40')
asm = asm.replace('mov a c','41')
asm = asm.replace('mov b a','42')
asm = asm.replace('mov b c','43')
asm = asm.replace('mov c a','44')
asm = asm.replace('mov c b','45')
asm = asm.replace('mov a ','46 ')
asm = asm.replace('mov b ','47 ')
asm = asm.replace('mov c ','48 ')

asm = asm.replace('ld bc ','58 ')
asm = asm.replace('ld a bc','56')
asm = asm.replace('ld a ','50 ')
asm = asm.replace('ld b ','51 ')
asm = asm.replace('ld c ','52 ')
asm = asm.replace('wr a bc','57')
asm = asm.replace('wr a ','53 ')
asm = asm.replace('wr b ','54 ')
asm = asm.replace('wr c ','55 ')

asm = asm.replace('add a b','60')
asm = asm.replace('add a c','61')
asm = asm.replace('add b a','62')
asm = asm.replace('add b c','63')
asm = asm.replace('add c a','64')
asm = asm.replace('add c b','65')
asm = asm.replace('add a ','66 ')
asm = asm.replace('add b ','67 ')
asm = asm.replace('add c ','68 ')

asm = asm.replace('sub a b','70')
asm = asm.replace('sub a c','71')
asm = asm.replace('sub b a','72')
asm = asm.replace('sub b c','73')
asm = asm.replace('sub c a','74')
asm = asm.replace('sub c b','75')
asm = asm.replace('sub a ','76 ')
asm = asm.replace('sub b ','77 ')
asm = asm.replace('sub c ','78 ')

asm = asm.replace('mul a b','80')
asm = asm.replace('mul a c','81')
asm = asm.replace('mul b a','82')
asm = asm.replace('mul b c','83')
asm = asm.replace('mul c a','84')
asm = asm.replace('mul c b','85')
asm = asm.replace('mul a ','86 ')
asm = asm.replace('mul b ','87 ')
asm = asm.replace('mul c ','88 ')

asm = asm.replace('div a b','90')
asm = asm.replace('div a c','91')
asm = asm.replace('div b a','92')
asm = asm.replace('div b c','93')
asm = asm.replace('div c a','94')
asm = asm.replace('div c b','95')
asm = asm.replace('div a ','96 ')
asm = asm.replace('div b ','97 ')
asm = asm.replace('div c ','98 ')

asm = asm.replace('dbg','250')
asm = asm.replace('ide','251')
asm = asm.replace('ret','255')

print('Calculating labels...')

out = asm.split(' ')
out = list(filter(None, out))


for ind, com in enumerate(out):
    if com.startswith('lbl_'):
        lab = out[ind].replace('lbl_','')
        labi = ind
        #del out[ind]
        lbln.append(str(lab))
        lbli.append(str(labi))
        

for ind, com in enumerate(out):
    for nam in lbln:
        if com in nam:
            out.insert(ind+1,'000')
lbln = []
lbli = []

for ind, com in enumerate(out):
    if com.startswith('lbl_'):
        lab = out[ind].replace('lbl_','')
        labi = ind
        del out[ind]
        lbln.append(str(lab))
        lbli.append(str(labi))


for ind, nam in enumerate(lbln):
    for indc, com in enumerate(out):
        if (com == nam):
            out[indc] = str(list(divmod(int(lbli[ind]), 256))[0])
            out[indc+1] = str(list(divmod(int(lbli[ind]), 256))[1])

for ind, i in enumerate(out):
    if (i.startswith('-')):
        a = i[1:]
        a = 256-int(a)
        out[ind] = a

for ind, i in enumerate(out):
    if (i.startswith('*')):
        a = i[1:]
        a = ord(a)
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
    cvm = '255\nAssemble Failed'
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

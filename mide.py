import os
os.system('color 17')
filename = 'bios.asm'

try:
    f_in = open(filename)
    f_in = f_in.read()
    f_in = f_in.split('\n')
except:
    f_in = []
tmp = 0
while (tmp<65536):
    f_in.append('')
    tmp = tmp + 1

print('Mini IDE v3')
while (True):
    instr = input()
    if (instr == 'list' or instr == 'l'):
        print()
        for ind, i in enumerate(f_in):
            if (i):
                print(str(ind) + '\t' + str(f_in[ind]))
        print()
        
    elif (instr == 'save' or instr == 's'):
        f_out = open(filename, 'w')
        savefile = ''
        for i in f_in:
            if (i != ''):
                if (savefile):
                    savefile = savefile + '\n' + i
                else:
                    savefile = i
        f_out.write(savefile)
        f_out.close()
        
    elif (instr.startswith('ins ') or instr.startswith('add ')):
        instr = instr[4:]
        try:
            list.insert(int(instr), 'nop')
        except:
            pass

    elif (instr == 'auto' or instr == 'a'):
        print('X to stop')
        ii = 0
        while (instr.lower() != 'x'):
            instr = input('[Auto] ' + str(ii) + ' # ')
            if (instr.lower() != 'x'):
                f_in[ii] = instr
            ii = ii+1

    elif (instr.startswith('del ')):
        try:
            instr = instr[4:]
            instr = int(instr)
            del f_in[instr]
        except:
            pass
        
    elif (instr == 'load' or instr == 'r'):
        try:
            f_in = open(filename)
            f_in = f_in.read()
            f_in = f_in.split('\n')
            for ind, i in enumerate(f_in):
                if (i == ''):
                    del f_in[ind]
        except:
            f_in = []
            tmp = 0
        while (tmp<65536):
            f_in.append('')
            tmp = tmp + 1
            
    elif (instr == 'build' or instr == 'b'):
        os.system('python asm.py')

    elif (instr == 'exit' or instr == 'x'):
        exit()

    elif (instr == 'cls' or instr == 'clear'):
        os.system('cls')

    elif (instr.startswith('color ')):
        try:
            instr = instr[6:]
            os.system('color ' +  instr)
        except:
          pass

    elif (instr == 'help' or instr == 'h'):
        print()
        print('list')
        print('save')
        print('load')
        print('auto')
        print('ins x')
        print('del x')
        print('color x')
        print('build')
        print('cls')
        print('exit')
        print()
        
    else:
        inarr = instr.split()
        if (len(inarr) > 1):
            try:
                f_in[int(inarr[0])] = instr.replace(inarr[0]+' ','')
            except:
                pass

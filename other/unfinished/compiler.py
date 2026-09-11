src = 'if x = 5 then if x = 10 then let x = 3 end end print x'

#
#	if x < 5 then
#		x = 3
#	end
#	print x
#

src = src.replace('\n',' ')
src = src.split(' ')
vars = 'abcxyz'
out = '''
_var_a: 0
_var_b: 0 
_var_c: 0
_var_x: 0
_var_y: 0
_var_z: 0

'''

lbls = 0
depth = 0
isthen = 0
for ind, i in enumerate(src):
	if (depth>0 and isthen==0):
		if (i == '<'):
			out+='jn addr\n'
		elif (i == '>'):
			out+='jp addr\n'
		elif (i == '=='):
			out+='jz addr\n'
		elif (i == '!='):
			out+='jnz addr\n'
		elif (i in vars):
			out+='mov a _var_'+str(i)+'\n'
		else:
			out+='mov b '+str(i)+'\n'
			
	if (i == 'if'):
		depth+=1
		isthen=0
	if (i == 'then'):
		out+='c'
		isthen=1
	if (i == 'end' and isthen == 1):
		depth-=1
		
		
print(out)
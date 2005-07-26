# import sys
# sys.path.append(r"D:\projets\tst\python")
# sys.path.append(r"D:\projets\tst\python\Debug CRM")

try:
	from tst import *
	from time import clock
	from random import shuffle

	print 'TST version : %s'%TST_VERSION

	ITERATIONS = range(500000)
	shuffle(ITERATIONS)

	t = TST()

	c = clock()
	for i in ITERATIONS:
		number = '%i'%i
	print 'Build : %f'%(clock()-c)

	c = clock()
	for i in ITERATIONS:
		number = '%i'%i
		t[number]=i
	print 'Write : %f'%(clock()-c)

	t.pack()

	c = clock()
	for i in ITERATIONS:
		number = '%i'%i
		assert t[number]==i
	print 'Read : %f'%(clock()-c)
except:
	import traceback
	traceback.print_exc()
	raw_input()

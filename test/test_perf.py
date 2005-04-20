from tst import *
from time import clock

t = TST()

c = clock()
for i in xrange(4000000):
    number = '%i'%i
print 'Build : %f'%(clock()-c)

c = clock()
for i in xrange(4000000):
    number = '%i'%i
    t[number]=1
print 'Write : %f'%(clock()-c)

t.pack()

c = clock()
for i in xrange(4000000):
    number = '%i'%i
    r = t[number]
print 'Read : %f'%(clock()-c)

raw_input("OK")

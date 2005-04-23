from tst import *
from time import clock

t = TST()

c = clock()
for i in xrange(400000):
    number = '%i'%i
print 'Build : %f'%(clock()-c)

c = clock()
for i in xrange(400000):
    number = '%i'%i
    t[number]=i
print 'Write : %f'%(clock()-c)

t.pack()

c = clock()
for i in xrange(400000):
    number = '%i'%i
    r = t[number]
    assert r==i
print 'Read : %f'%(clock()-c)

raw_input("OK")

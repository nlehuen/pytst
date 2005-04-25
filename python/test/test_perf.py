from tst import *
from time import clock

ITERATIONS = 1000000

t = TST()

c = clock()
for i in xrange(ITERATIONS):
    number = '%i'%i
print 'Build : %f'%(clock()-c)

c = clock()
for i in xrange(ITERATIONS):
    number = '%i'%i
    t[number]=i
print 'Write : %f'%(clock()-c)

t.pack()

c = clock()
for i in xrange(ITERATIONS):
    number = '%i'%i
    r = t[number]
    assert r==i
print 'Read : %f'%(clock()-c)

raw_input("OK")

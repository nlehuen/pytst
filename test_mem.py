from tcc import tst
import sys

a = 'toto'
ca1 = sys.getrefcount(a)
ca2 = sys.getrefcount(None)

print ca1, ca2

t=tst.TST()

assert(sys.getrefcount(None)==ca2+1)

assert(sys.getrefcount(a)==ca1)

t[a]=a

assert(sys.getrefcount(a)==ca1+1)

a2 = t.put(a,'coucou')

assert(sys.getrefcount(a)==ca1+1)

del(a2)

assert(sys.getrefcount(a)==ca1)

l=t.walk(None,tst.ListAction())

assert(sys.getrefcount(a)==ca1)

t[a]=a

assert(sys.getrefcount(a)==ca1+1)

l=t.walk(None,tst.ListAction())

assert(sys.getrefcount(a)==ca1+2)

del(l)

assert(sys.getrefcount(a)==ca1+1)

d=t.walk(None,tst.DictAction())

assert(sys.getrefcount(a)==ca1+3)

del(d)

assert(sys.getrefcount(a)==ca1+1)

del(t)

assert(sys.getrefcount(a)==ca1)

assert(sys.getrefcount(None)==ca2)


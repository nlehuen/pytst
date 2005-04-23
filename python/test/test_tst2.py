import tst
from tcc.util import levenshtein
import time

f = tst.CallableFilter(lambda k,d,o: o)


t = tst.TST()
u = tst.TST()

start = time.time()
for i in range(5):
    for line in file('prenoms.txt','r').readlines():
        line=line.strip()
        t[line]=line
        u[line]=len(line)
print 'Python version : ',time.time()-start

for s in ('Nicolas;H','Yohan;H'):
    for i in range(7):
        print "almost(%i)"%i
        _dict = t.almost(s,i,f,tst.DictAction())
        print len(_dict)
        print _dict
        for key,item in _dict.items():
            d = levenshtein(key,s);
            assert(d<=i)
            assert(d==(i-item[0]))
        print 'OK'
import tst,tcc.tst
import time

t = tst.string_tst(8,'')
u = tst.int_tst(8,0)

start = time.time()
for i in range(100):
    for line in file('prenoms.txt','r'):
        line=line.strip()
        t.put(line,line)
        u.put(line,len(line))
print 'C++ version : ',time.time()-start

t=tcc.tst.TST()
u=tcc.tst.TST()

start = time.time()
for i in range(100):
    for line in file('prenoms.txt','r'):
        line=line.strip()
        t[line]=line
        u[line]=line
print 'Python version : ',time.time()-start

#t.adjust()
#u.adjust()
#
#for line in file('prenoms.txt','r'):
#    line=line.strip()
#    print t.get(line), u.get(line)

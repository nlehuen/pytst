import tst,tcc.tst
import time

t = tst.TST(8,'')
u = tst.IntegerTST(8,0)

start = time.time()
for i in range(50):
    for line in file('prenoms.txt','r').readlines():
        line=line.strip()
        t.put(line,line)
        u.put(line,len(line))
print 'C++ version : ',time.time()-start

class action(tst.Action):
    def __init__(self):
        tst.Action.__init__(self)
        self._dict=dict()

    def perform(self,key,diff,data):
        if self._dict.has_key(key):
            odiff, odata = self._dict[key]
            if odiff<diff:
                self._dict[key]=(diff,data)
        else:
            self._dict[key]=(diff,data)

s = 'Nicolas;H';
a = action()
t.almost(s,len(s),3,a)

print 'The END !'

print a._dict

t=tcc.tst.TST()
u=tcc.tst.TST()

start = time.time()
for i in range(50):
    for line in file('prenoms.txt','r').readlines():
        line=line.strip()
        t[line]=line
        u[line]=len(line)
print 'Python version : ',time.time()-start

#t.adjust()
#u.adjust()
#
#for line in file('prenoms.txt','r'):
#    line=line.strip()
#    print t.get(line), u.get(line)

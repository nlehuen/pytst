import tst
from tcc.util import levenshtein

import time

t = tst.TST(8,'')
u = tst.IntegerTST(8,0)

start = time.time()
for i in range(5):
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

for s in ('Nicolas;H','Yohan;H'):
    for i in range(7):
        print "almost(%i)"%i
        _dict = t.almost(s,len(s),i).items();
        print len(_dict)
        for key,item in _dict:
            d = levenshtein(key,s);
            assert(d<=i)
            assert(d==(i-item[0]))
        print 'OK'

def test(key,dist,data):
    print 'test',key,dist,data

def predicate(data):
    # raise Exception, 'coucou'
    return data[:5]

la = tst.ListAction(None);
t.walk(la)
print len(la.get_list())

la = tst.DictAction(predicate);
t.walk(la)
print la.get_dict()

la = tst.CallableAction(test);
t.common_prefix('Nico',la)

print t.get_maximum_key_length()

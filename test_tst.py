# -*- coding: CP1252 -*-
from tcc import tst
#from tcc.util import levenshtein

import time

t = tst.TST(8,None)
u = tst.IntegerTST(8,0)

start = time.time()
for i in range(5):
    for line in file('prenoms.txt','r').readlines():
        line=line.strip()
        t.put(line,line)
        u.put(line,len(line))
print 'C++ version : ',time.time()-start

class action(tst.Action):
    counter = 0

    def __init__(self):
        tst.Action.__init__(self)
        self._dict=dict()
        self._id = action.counter
        action.counter+=1
    def perform(self,key,diff,data):
        if self._dict.has_key(key):
            odiff, odata = self._dict[key]
            if odiff<diff:
                self._dict[key]=(diff,data)
        else:
            self._dict[key]=(diff,data)
    def result(self):
        #TODO: problème ici car la référence n'est pas incrémentée...
        #print "_result_%i"%self._id
        return self._dict
    def __del__(self):
        #print "_dl_%i"%self._id
        tst.Action.__del__(self)

for s in ('Nicolas;H','Yohan;H'):
    print '------------',s
    for i in range(7):
        # print "almost(%i)"%i
        print len(t.almost(s,i,None,tst.DictAction()))

print 'maximum key length :', t.get_maximum_key_length()

import re
r = re.compile('(.*)[;=](.*)')

start = time.time()
for i in range(5000):
    print i
    la = action();
    #TODO: si on enlève le "d=" le résultat est immédiatement décrémenté ce qui coince quand on passe au bench suivant...
    t.walk(tst.CallableFilter(lambda x,y,z: r.match(z).group(1)),la)
print 'la en python : ',time.time()-start

start = time.time()
for i in range(500):
    la = tst.DictAction();
    t.walk(tst.CallableFilter(lambda x,y,z: r.match(z).group(1)),la)
print 'la en C++ : ',time.time()-start

start = time.time()
for i in range(500):
    la = tst.DictAction();
    t.walk(None,la)
print 'la en C++ sans filter : ',time.time()-start

start = time.time()
for i in range(500):
    la = tst.ListAction()
    t.walk(None,la)
print 'listaction en C++ sans filter: ',time.time()-start

start = time.time()
for line in file('prenoms.txt','r').readlines():
    line = line.strip()
    t.put(line,line+str(i))
    la1 = tst.ListAction()
    la2 = tst.DictAction()
    t.almost(line,4,None,la1)
    t.common_prefix(line,None,la2)
    t.almost(line+line,4,None,la1)
    t.common_prefix(line+line,None,la2)
print time.time()-start

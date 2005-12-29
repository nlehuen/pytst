# -*- coding: iso-8859-1 -*-
import tst
from tcc.util import levenshtein

import time, sys

filt = tst.CallableFilter(lambda k,d,o: o)

t = tst.TST()
u = tst.TST()

print 'Loading file'
start = time.time()
for i in range(5):
    for line in file('prenoms.txt','r').readlines():
        line=line.strip()
        t[line]=line
        u[line]=len(line)
print 'C++ version : ',time.time()-start

class action(object):
    counter = 0

    def __init__(self):
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
       
for s in ('Nicolas;H','Yohan;H'):
    print '------------',s
    for i in range(7):
        # print "close_match(%i)"%i
        print len(t.close_match(s,i,filt,tst.DictAction()))

print 'maximum key length :', t.get_maximum_key_length()

import re
r = re.compile('(.*)[;=](.*)')

f = lambda x,y,z: r.match(z).group(1)
frc = sys.getrefcount(f) 
nrc = sys.getrefcount('Lionel;H')

start = time.time()
for i in range(500):
    print i
    la = action();
    #TODO: si on enlève le "d=" le résultat est immédiatement décrémenté ce qui coince quand on passe au bench suivant...
    t.walk(tst.CallableFilter(f),tst.CallableAction(la.perform,la.result))
print 'la en python : ',time.time()-start

start = time.time()
for i in range(500):
    la = tst.DictAction();
    t.walk(tst.CallableFilter(lambda x,y,z: r.match(z).group(1)),la)
print 'la en C++ : ',time.time()-start

start = time.time()
for i in range(500):
    la = tst.DictAction();
    t.walk(filt,la)
print 'la en C++ sans filter : ',time.time()-start

start = time.time()
for i in range(500):
    la = tst.ListAction()
    t.walk(filt,la)
print 'listaction en C++ sans filter: ',time.time()-start

start = time.time()
for line in file('prenoms.txt','r').readlines():
    line = line.strip()
    t[line]=line+str(i)
    for k,v in t.close_match(line,4,filt,tst.DictAction()).items():
        ld = levenshtein(line,k)
        if ld!=(4-v[0]):
            print line, k, ld, 4-v[0]
    t.prefix_match(line,filt,tst.ListAction())
    t.close_match(line+line,4,filt,tst.DictAction())
    t.prefix_match(line+line,filt,tst.ListAction())
print time.time()-start

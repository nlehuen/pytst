# -*- coding: CP1252 -*-
from tcc import tst
import sys

print tst._tst.__file__
assert tst._tst.__file__==r'c:\projets\development\python\tcc\_tst_d.pyd'

for i in xrange(1000000000):
    print '>------->',sys.gettotalrefcount()
    t=tst.TST()
    t['PARIS']='PARIS'
    t['PARIS 15']='PARIS 15'
    t['PARIS 15EME']='PARIS 15EME'
    t['PARIS 15ème']='PARIS 15ème 2'
    # t['PARIS 15EME ARRONDISSEMENT']='PARIS 15EME ARRONDISSEMENT'
    
    print 'aaa',sys.getrefcount(t['PARIS 15EME'])

    print t['PARIS 15']
    
    print 'Maximum key length :',t.get_maximum_key_length()
    
    d = tst.DictAction()
    
    print t.almost('PARIS',3,None,d)
    print t.almost('PARIS 15',5,None,tst.DictAction())
    print t.almost('PARIS 15EME ARRONDISSEMENT',3,None,tst.DictAction())
    print '------------------------------------------------------------'
    print t.common_prefix('PAR',None,tst.ListAction())
    print t.common_prefix('PARIS',None,tst.ListAction())
    print t.common_prefix('PARIS 15',None,tst.ListAction())
    print t.common_prefix('PARIS 15EME',None,tst.ListAction())
    print t.common_prefix('PARIS 15EME ARRONDISSEMENT',None,tst.ListAction())
    print t.common_prefix('PARIS 17EME ARRONDISSEMENT',None,tst.ListAction())
    print t.common_prefix('',None,tst.ListAction())
    print t.common_prefix('P',None,tst.ListAction())
    print t.common_prefix('PYTHON',None,tst.ListAction())
    
    print 1+1
    
    del(d)
    
    print 'bbb',sys.getrefcount(t['PARIS 15EME'])
    
    #def walk(key,dist,data):
    #    print 'walk:',key,dist,data
        
    #t.walk(None,tst.CallableAction(walk,None))
    
    #def perform(key,dist,data):
    #    print 'f:',data
    #    if not data:
    #        return '>'+key+'<'
    #
    #f = tst.CallableFilter(perform)
    
    #print '>',sys.gettotalrefcount()
    #print t.get_or_build('toto23',f)
    #print '>',sys.gettotalrefcount()
    #print t['toto23']
    #print '>',sys.gettotalrefcount()
    #r = t['PARIS 15']
    #print 'r:',sys.getrefcount(r)
    #t['PARIS 15']='PARIS 17'
    #print t['PARIS 15']
    #print 'r2:',sys.getrefcount(r)

    del(t)
    #del(walk)
    #del(f)
    #del(perform)
  
    print '<------------<',sys.gettotalrefcount()


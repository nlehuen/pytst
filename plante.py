# -*- coding: CP1252 -*-
from tcc import tst
import sys

print tst._tst.__file__
assert tst._tst.__file__.endswith(r'\_tst.pyd')

def prout(key,diff,value):
    print 'ukuk','"'+key+'"',diff,value

for i in xrange(1000000000):
    #print '>------->',sys.gettotalrefcount()
    t=tst.TST()
    t['PARIS']='PARIS'
    t['PARIS 15']='PARIS 15'
    t['PARIS 15EME']='PARIS 15EME'
    t['APP']='APPARTEMENT'
    t['APPT']='APPARTEMENT'
    t['APPARTEMENT']='APPARTEMENT'
    t['APP BEN COOL']='TEST TEST TEST'
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

    print '>>>>>>>>>'
    # print t.scan('Bonjour  APPARITION PARIS ca va PARIS 15 PARIS 17 YOUPI PARIS 15EME GUEH PARIS 2',tst.CallableAction(prout,None))
    print t.scan_with_stop_chars('LALA VARAPP Bonjour APPARITION APP PARIS APPT APP BEN ca va APP BEN COOL PARIS 15 PARIS APPARTEMENT 17 YOUPI PARIS 15EME GUEH PARIS APP 2 APPARemment APPA',' \t\r\n',tst.TupleListAction())
    print '>>>>>>>>>'

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

    #print '<------------<',sys.gettotalrefcount()


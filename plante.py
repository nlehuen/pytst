from tcc import tst

print tst._tst.__file__
assert tst._tst.__file__==r'c:\projets\development\python\tcc\_tst.pyd'

t=tst.TST()
t['PARIS']='PARIS'
t['PARIS 15']='PARIS 15'
t['PARIS 15EME']='PARIS 15EME'
# t['PARIS 15EME ARRONDISSEMENT']='PARIS 15EME ARRONDISSEMENT'

print t['PARIS 15']

print 'Maximum key length :',t.get_maximum_key_length()

print t.almost('PARIS',3,None,tst.DictAction())
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




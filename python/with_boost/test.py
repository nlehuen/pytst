import tst

class NullFilter(object):
    def perform(self,string,remaining,data):
        return data
        
class DictAction(object):
    def __init__(self):
        self.rd = {}
        
    def perform(self,string,remaining,data):
        t = self.rd.get(string)
        if (t is None) or t[1]>remaining:
            self.rd[string] = (data,remaining)
    
    def result(self):
        return self.rd
 
print 'init'
t = tst.TST()
t['toto'] = 'toto'
t['tata'] = 'tata'
t.pack()
t['tita'] = 'tita'
t.pack()

print
print 'Built-in actions'
print t.close_match("tota",1,tst.NullFilter(),tst.NullAction())
print t.close_match("tota",1,tst.NullFilter(),tst.DictAction())
print t.close_match("tota",1,tst.NullFilter(),tst.TupleListAction())
print t.close_match("tota",1,tst.NullFilter(),tst.ListAction())

print
print 'CallableAction'
da = DictAction()
print t.close_match("tota",1,tst.NullFilter(),tst.CallableAction(da.perform,da.result))

print
print 'CallableFilter'
nf = NullFilter()
print t.close_match("tota",1,tst.CallableFilter(nf.perform),tst.CallableAction(da.perform,da.result))

print
print 'Nones'
print t.walk(None,None)
print t.walk(None,None,"t")
print t.close_match("tota",1,None,None)

print
print 'Scan'
print t.scan('tototatatitatitititiiaiitita',tst.TupleListAction())
print t.scan_with_stop_chars('toto.tata tita tototata / titi titiiaiitita',' .',tst.TupleListAction())

print
print 'write'
t.write_to_file(file('test.tst','wb'))
print 'read'
t2 = tst.TST()
t2.read_from_file(file('test.tst','rb'))
print t2.walk(None,tst.DictAction())

print 'big write'
t = tst.TST()
for i in xrange(100000):
    s = '%i'%i
    t[s] = s
t.write_to_file(file('test.tst','wb'))
print 'big read'
t = tst.TST()
t.read_from_file(file('test.tst','rb'))
t.walk(None,tst.DictAction())

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
 
t = tst.TST()
t['toto'] = 'toto'
t['tata'] = 'tata'

print t.close_match("tota",1,tst.NullFilter(),tst.NullAction())
print t.close_match("tota",1,tst.NullFilter(),tst.DictAction())
print t.close_match("tota",1,tst.NullFilter(),tst.TupleListAction())
print t.close_match("tota",1,tst.NullFilter(),tst.ListAction())

da = DictAction()
print t.close_match("tota",1,tst.NullFilter(),tst.CallableAction(da.perform,da.result))

nf = NullFilter()
print t.close_match("tota",1,tst.CallableFilter(nf.perform),tst.CallableAction(da.perform,da.result))

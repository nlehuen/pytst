import tst

# class NullFilter(tst.Filter):
#     def perform(string,remaining,data):
#         return data
#         
# class DictAction(tst.Action):
#     def __init__(self):
#         self.rd = {}
#         
#     def perform(self,string,remaining,data):
#         t = self.rd.get(string)
#         if (t is None) or t[1]>remaining:
#             self.rd[string] = (data,remaining)
#     
#     def result(self):
#         return self.rd
# 
t = tst.TST()
t['toto'] = 'toto'
t['tata'] = 'tata'

print t.close_match("tota",1,tst.NullFilter(),tst.NullAction())

print t.close_match("tota",1,tst.NullFilter(),tst.DictAction())

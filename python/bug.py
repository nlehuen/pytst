import sys
sys.path.insert(0,r'D:\projets\tst\python\Debug')
import tst

t = tst.TST()
t['ccc'] = 1
print t.scan('cc',tst.DictAction())

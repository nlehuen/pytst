from tcc.tst import *

t = TST()

t['Nicolas']='Nicolas'
t['Nicolas-Antoinette']='Nicolas-Antoinette'
t['Antoinette']='Antoinette'
t['Antoine']='Antoine'
t['astride']='astride'

print t.scan('Nicolas',TupleListAction())
print t.scan('Nicolasstupide',TupleListAction())
print t.scan('Nicolast',TupleListAction())
print t.scan('Antoinette Antoinette',TupleListAction())
print t.scan('Nicolas-Antoinette',TupleListAction())
print t.scan('Nicolas-Antoine',TupleListAction())
print
print t.scan_with_stop_chars('Nicolas',' -',TupleListAction())
print t.scan_with_stop_chars('Nicolasstupide',' -',TupleListAction())
print t.scan_with_stop_chars('Nicolast',' -',TupleListAction())
print t.scan_with_stop_chars('Antoinette Antoinette',' -',TupleListAction())
print t.scan_with_stop_chars('Nicolas-Antoinette',' -',TupleListAction())
print t.scan_with_stop_chars('Nicolas-Antoine',' -',TupleListAction())



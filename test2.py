from tst import *

t = TST()

t["abc"] = "abc"
t["abcdef"] = "abcdef"
t["abcdefgh"] = "abcdefgh"
t["01"]="01"
t["02"]="02"
print t["abc"]
print t["01"]
print t["foobar"]

print t.scan("abc",TupleListAction())
print t.scan("01",TupleListAction())
print t.scan("abc01",TupleListAction())
print t.scan("abc---01",TupleListAction())
print t.scan("abcdef---abc--01--abcdef--abc",TupleListAction())

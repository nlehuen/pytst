import tst

t = tst.string_tst(8,'')
u = tst.int_tst(8,0)

for line in file('prenoms.txt','r'):
    line=line.strip()
    t.put(line,line)
    u.put(line,len(line))

t.adjust()
u.adjust()

for line in file('prenoms.txt','r'):
    line=line.strip()
    print t.get(line), u.get(line)

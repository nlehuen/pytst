from tst import *
from time import clock

try:
    raise Exception()
    f = file('test.tst','rb')
    global t
    t = TST(f)
    f.close()
except:
    global t
    t = TST()
    
    c = clock()

    string_size = 0
    for i in xrange(10000000):
        if i%1000 == 0:
            print t.bytes_allocated()
        number = '%i'%i
        string_size += len(number)
        t[number]=1
    t.pack()

    print 'load_time : %f'%(clock()-c)
    print 'string_size : %i'%string_size
    print 'packed : %i'%t.bytes_allocated()

#     print 'Writing...'
#     f = file('test.tst','wb')
#     t.write(f)
#     f.close()

to_scan = '3214g5q4sd65gfq6s5dg6q5fhsfghjjdfgj654564654654653213564654654646543203210.30316313216343641313.10.301'

c = clock()
for i in xrange(100000):
    t.scan(to_scan,TupleListAction())
print 'scan of %i chars : %f ms'%(len(to_scan),(clock()-c)/100.0)

c = clock()
for i in xrange(10000):
    t.almost('123456',1,None,TupleListAction())
print 'almost(1) : %f ms'%((clock()-c)/10)

c = clock()
for i in xrange(1000):
    t.almost('123456',2,None,TupleListAction())
print 'almost(2) : %f ms'%(clock()-c)

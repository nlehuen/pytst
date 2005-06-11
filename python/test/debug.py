from traceback import print_exc
from random import shuffle

if __name__=='__main__':
    try:
        import sys
        sys.path.append(r"C:\projets\development\tst-PythonReference\python")
        sys.path.append(r"C:\projets\development\tst-PythonReference\python\Debug")
        from tst import *
        
        t = TST()
        
        r = range(10000)
        
        shuffle(r)

        for i in r:
            t[str(i)] = i
        
        shuffle(r)
        
        for i in r:
            assert t[str(i)] == i
        
        print "asserts OK"
        
#         f = file("output.tst","wb")
#         try:
#             t.write(f)
#         finally:
#             f.close()
#         print 'write OK'
#         
#         f = file("output.tst","rb")
#         try:
#             t2 = TST(f)
#         finally:
#             f.close()
#         print 'read OK'
    except:
        print_exc()
        raw_input()

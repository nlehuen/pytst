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
        
        t.walk(None,None)
        print t.almost("1234",1,None,DictAction())
        
        f = file(r"c:\temp\output.tst","wb")
        try:
            t.write_to_file(f)
        finally:
            f.close()
        print 'write OK'
        
        for i in range(100):
			f = file(r"c:\temp\output.tst","rb")
			try:
				t2 = TST()
				t2.read_from_file(f)
				shuffle(r)
				for i in r:
					assert t2[str(i)]==i
			finally:
				f.close()
			print 'read OK'
    except:
        print_exc()
        raw_input()

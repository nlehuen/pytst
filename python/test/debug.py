from traceback import print_exc

if __name__=='__main__':
    try:
        import sys
        sys.path.append(r"C:\projets\development\tst-PythonReference\python")
        sys.path.append(r"C:\projets\development\tst-PythonReference\python\Debug")
        from tst import *
        
        t = TST()
        
        for i in xrange(1000):
            t[str(i)] = i
        
        for i in xrange(1000):
            assert t[str(i)] == i
        
        f = file("output.tst","wb")
        t.write(f)
        f.close()
    except:
        print_exc()
        raw_input()

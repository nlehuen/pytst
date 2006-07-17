if __name__ == "__main__":
    import sys
    from time import time
    import linecache
    import glob
    from textindex import textindex
    import traceback
    import linecache

    ti = textindex()
    
    try:
        start = time()
        ti.read('text.ti')
        print 'Loading time : %.2fs'%(time()-start)
    except:
        traceback.print_exc()
        
        start = time()
        lines = 0
        for f in glob.glob('*.txt'):
            print f,
            for linenumber, line in enumerate(file(f,'rb')):
                lines += 1
                line = line.strip()
                ti.put_text(line.lower().decode('iso-8859-1'),'%12s:%04i'%(f,linenumber))
                if linenumber % 100 == 0:
                    sys.stdout.write('.')
            print 'OK'
        ti.pack()
        print 'Indexing time : %.2fs for %i lines'%(time()-start,lines)

        ti.write('text.ti')
    
    def lines(text,intersection=True):
        for ln, r in ti.find_text(text.lower(),intersection):
            print '%02i:%s'%(
                r,
                ln
            ),

    def ilines(text,intersection=True):
        for ln, r in ti.find_text(text.lower(),intersection):
            print '%02i:%s'%(
                r,
                ln,
            ),

    if len(sys.argv)>1 and sys.argv[1]=='gui':
        from Tkinter import *
        class Explorer(object):
            def __init__(self,master):
                self.frame = Frame(master)
                self.frame.pack(fill=BOTH, expand=1)
                
                self.entry = Entry(self.frame, name='input')
                self.entry.pack(fill=X)
                self.entry.bind('<KeyRelease>',self.keyPressed)
                
                frame = Frame(self.frame)
                frame.pack(fill=BOTH, expand=1)
                scrollbar = Scrollbar(frame, orient=VERTICAL)
                self.list = Listbox(frame, name='list', yscrollcommand=scrollbar.set)
                scrollbar.config(command=self.list.yview)
                scrollbar.pack(side=RIGHT, fill=Y)
                self.list.pack(side=LEFT, fill=BOTH, expand=1)
                
                self.label = Label(self.frame, name='count')
                self.label.pack()
            
            def keyPressed(self,event):
                self.list.delete(0,END)
                start = time()
                result = ti.find_text(self.entry.get().lower(),True)
                # result.sort(key=lambda i : -i[1])
                elapsed = time() - start
                for ln, r in result[:100]:
                    i = ln.rindex(':')
                    d = ln[:i].strip()
                    l = int(ln[i+1:])
                    self.list.insert(END,'%02i:%s:%i:%s'%(
                        r,
                        d,
                        l,
                        linecache.getline(d,l+1).strip()
                    ))
                self.label.config(text = '%i lines in %.2fs'%(
                    len(result),
                    elapsed
                ))
                
        root = Tk()
        explorer = Explorer(root)
        root.mainloop()

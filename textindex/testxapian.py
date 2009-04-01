if __name__ == "__main__":
    import sys
    from time import time
    import linecache
    import glob
    import traceback
    import linecache
    import xapian
    import re

    stem = xapian.Stem("french")
    ti = xapian.inmemory_open()
    ti = xapian.WritableDatabase("test.ti", xapian.DB_CREATE_OR_OPEN)
    # ti = xapian.quartz_open('test.idx')

#     start = time()
#     lines = 0
#     for f in glob.glob('*.txt'):
#         print f,
#         for linenumber, line in enumerate(file(f,'rb')):
#             lines += 1
#             line = line.strip()
#             doc = xapian.Document()
#             doc.set_data('%12s:%04i'%(f,linenumber))
#             for word_number, word in enumerate(re.findall(r'\w+',line.lower())):
#                 doc.add_posting(word,word_number)
#             ti.add_document(doc)
#             if linenumber % 100 == 0:
#                 sys.stdout.write('.')
#         print 'OK'
#     print 'Indexing time : %.2fs for %i lines'%(time()-start,lines)
    
    if len(sys.argv)>1 and sys.argv[1]=='gui':
        from Tkinter import *
        class Explorer(object):
            def __init__(self,master):
                self.frame = Frame(master)
                self.frame.pack(fill=BOTH, expand=1)
                
                self.entry = Entry(self.frame, name='input')
                self.entry.pack(fill=X)
                self.entry.bind('<Key>',self.keyPressed)
                
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
                if self.entry.get():
                    query_parser = xapian.QueryParser()
                    enq = xapian.Enquire(ti)
                    query = query_parser.parse_query(self.entry.get(),query_parser.FLAG_WILDCARD)
                    print query.get_description()
                    enq.set_query(query)        
                    elapsed = time() - start
                    result = enq.get_mset(0,100)
                    count = 0
                    for doc in result:
                        count += 1
                        ln = doc[4].get_data()
                        r = doc[1]
                        i = ln.rindex(':')
                        d = ln[:i].strip()
                        l = int(ln[i+1:])
                        self.list.insert(END,'%.2f:%s:%i:%s'%(
                            r,
                            d,
                            l,
                            linecache.getline(d,l+1).strip()
                        ))
                    self.label.config(text = '%i lines in %.2fs'%(
                        count,
                        elapsed
                    ))
                
        root = Tk()
        explorer = Explorer(root)
        root.mainloop()

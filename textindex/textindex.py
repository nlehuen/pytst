# -*- coding: iso-8859-1 -*-

from tst import *
from itertools import groupby
import re

re_word = re.compile(r'\b\w+\b')

class Collector(object):
    def __init__(self,result):
        self._result = result
        
    def perform(self,string,remaining_distance,data):
        for key in data:
            self._result[key] = self._result.get(key,0) + 1
    
    def result(self):
        return self._result

def intersect(d1,d2):
    for k, v in d2.iteritems():
        if k in d1:
            d1[k] += v
    for k in d1.keys():
        if k not in d2:
            del d1[k]
    return d1    

class textindex(object):
    def __init__(self):
        self.tst = TST()
        
    def add(self,text,key):
        for word in re_word.finditer(text.lower()):
            word = word.group(0)
            s = self.tst.get(word)
            if s is None:
                s = list()
                self.tst.put(word,s)
            s.append(key)
    
    def remove(self,key):
        def r(string,remaining_distance,data):
            data.discard(key)
        self.tst.walk(None,CallableAction(r,None))
    
    def find_incremental(self,text,intersection=True):
        if intersection:
            result = []
            for word in re_word.finditer(text.lower()):
                word = word.group(0)
                collector = Collector(dict())
                result.append(self.tst.walk(None,CallableAction(collector.perform,collector.result),word))
            
            # Calcul de l'intersection en sommant les résultats
            intersection = result[0]
            for d in result[1:]:
                intersection = intersect(intersection,d)
            result = intersection
        else:
            collector = Collector(dict())
            for word in re_word.finditer(text.lower()):
                word = word.group(0)
                self.tst.walk(None,CallableAction(collector.perform,collector.result),word)
            result = collector.result()
            
        
        # Tri selon le rang décroissant   
        return sorted(result.iteritems(),key=lambda i : -i[1])
    
    def find(self,text,intersection=True):
        if intersection:
            result = []
            for word in re_word.finditer(text.lower()):
                word = word.group(0)
                
                current_result = dict()
                keys = self.tst.get(word)
                if keys is not None:
                    for key in keys:
                        current_result[key] = current_result.get(key,0) + 1
                
                result.append(current_result)
            
            # Calcul de l'intersection en sommant les résultats
            intersection = result[0]
            for d in result[1:]:
                intersection = intersect(intersection,d)
            result = intersection
        else:
            result = dict()
            for word in re_word.finditer(text.lower()):
                word = word.group(0)
                keys = self.tst.get(word)
                if keys is not None:
                    for key in keys:
                        result[key] = result.get(key,0) + 1
        
        # Tri selon le rang décroissant   
        return sorted(result.iteritems(),key=lambda i : -i[1])
    
    def pack(self):
        self.tst.pack()
    
    def words(self):
        class C(CallableAction):
            def __init__(self):
                self.c = 0
        
            def perform(self,string,remaining_distance,data):
                self.c += 1
            
            def result(self):
                return self.c
        c = C()
        return self.tst.walk(None,c)

if __name__ == "__main__":
    import sys
    from time import time
    import linecache


    ti = textindex()
    
    start = time()
    lines = 0
    for f in ('12137-8.txt','8act310.txt','8act110.txt'):
        for linenumber, line in enumerate(file(f,'rb')):
            lines += 1
            ti.add(line,(f,linenumber))
            if linenumber % 100 == 0:
                sys.stdout.write('.')
        print 'OK'
    ti.pack()
    print 'Indexing time : %.2fs for %i lines'%(time()-start,lines)
    
    def lines(text,intersection=True):
        for ln, r in ti.find(text,intersection):
            print '%i:%s:%i:%s'%(
                r,
                ln[0],
                ln[1],
                linecache.getline(ln[0],ln[1]+1)
            ),

    def ilines(text,intersection=True):
        for ln, r in ti.find_incremental(text,intersection):
            print '%i:%s:%i:%s'%(
                r,
                ln[0],
                ln[1],
                linecache.getline(ln[0],ln[1]+1)
            ),

    if len(sys.argv)>1 and sys.argv[1]=='gui':
        from Tkinter import *
        class Explorer(object):
            def __init__(self,master):
                self.frame = Frame(master)
                self.frame.grid(sticky=W+E+N+S)
                
                self.entry = Entry(self.frame, name='input')
                self.entry.grid(row=0, column=0, columnspan=2, sticky=W+E)
                self.entry.bind('<Key>',self.keyPressed)
                
                self.list = Listbox(self.frame, name='list')
                self.list.grid(row=1, column=0, sticky=W+E+N+S)
                
                self.label = Label(self.frame, name='count')
                self.label.grid(row=2,column=0,columnspan=2, sticky=W+E)
            
            def keyPressed(self,event):
                self.list.delete(0,END)
                start = time()
                result = ti.find_incremental(self.entry.get())
                elapsed = time() - start
                for ln, r in result:
                    self.list.insert(END,'%02i:%16s:%5i:%s'%(
                        r,
                        ln[0],
                        ln[1],
                        linecache.getline(ln[0],ln[1]+1)
                    ))
                self.label.config(text = '%i lines in %.2fs'%(
                    len(result),
                    elapsed
                ))
                
        root = Tk()
        explorer = Explorer(root)
        root.mainloop()

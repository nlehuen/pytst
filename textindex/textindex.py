# -*- coding: iso-8859-1 -*-

from tst import *
from itertools import groupby
import re

re_word = re.compile(r'\b\w+\b')

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
    
    def find_incremental(self,text):
        result = []
        def r(string,remaining_distance,data):
            result.extend(data)
        for word in re_word.finditer(text.lower()):
            word = word.group(0)
            self.tst.walk(None,CallableAction(r,None),word)
        
        # Calcul du rang et tri selon le rang décroissant   
        ranked = {}
        for key in result:
            ranked[key] = ranked.get(key,0) + 1
        ranked = sorted(ranked.iteritems(),key=lambda i : -i[1])
        
        return ranked
    
    def find(self,text):
        result = []

        for word in re_word.finditer(text.lower()):
            word = word.group(0)
            s = self.tst.get(word)
            if s:
                result.extend(s)
            
        ranked = {}
        for key in result:
            ranked[key] = ranked.get(key,0) + 1
        ranked = sorted(ranked.iteritems(),key=lambda i : -i[1])
        
        return ranked
    
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
    
    def lines(text):
        for ln, r in ti.find(text):
            print '%i:%s:%i:%s'%(
                r,
                ln[0],
                ln[1],
                linecache.getline(ln[0],ln[1]+1)
            ),

    def ilines(text):
        for ln, r in ti.find_incremental(text):
            print '%i:%s:%i:%s'%(
                r,
                ln[0],
                ln[1],
                linecache.getline(ln[0],ln[1]+1)
            ),

    start = time()
    
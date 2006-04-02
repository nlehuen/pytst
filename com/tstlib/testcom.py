# -*- coding: iso-8859-1 -*-

from win32com.client.gencache import EnsureDispatch as Dispatch
from win32com.client import Dispatch
import traceback
from time import clock
import linecache
import re

words_re = re.compile(r"\b[a-zA-Zéèâêôàçù]+\b")

def dump(ti,words,intersect=0,method="text"):
    print "Requesting %r..."%words,

    repeat = 100
    start = clock()
    if method=="text":
        for i in xrange(repeat):
           result = ti.FindTextA(words,intersect)
    else:
        for i in xrange(repeat):
           result = ti.FindWord(words)
    end = clock()
    print '%.2f ms per search'%(1000*(end-start)/repeat)
       
    for i in range(result.Size):
        document = result.GetDocument(i)
        try:
            sep = document.rindex(':')
            line = int(document[sep+1:])
            document = document[:sep]
            print document.decode('iso-8859-1'), line, result.GetScore(i), linecache.getline(document,line+1).decode('iso-8859-1'),
        except ValueError:
            print document.encode('iso-8859-1','ignore'), result.GetScore(i)

try:
    try:
        ti = Dispatch('tstlib.TextIndex')

        print "Version :",ti.Version

        # ---------------- petit test sans conséquence
        
        ti.AddText('bonjour, je suis nicolas','1')
        ti.AddText('bonjour, je suis alfred','2')
        ti.AddText('alfred hitchcock','3')
        ti.AddText('bonjour comment allez-vous ?','3')
        
        dump(ti,'bonjour')
        dump(ti,'bonjour comment alfred',0)
        dump(ti,'bonjour comment alfred',1)

        print "Saved %s !"%ti.Save(r'c:\temp\test.ti')
        ti = Dispatch('tstlib.TextIndex')
        print "Loaded %s !"%ti.Load(r'c:\temp\test.ti')
        print
        
        dump(ti,'bonjour')
        dump(ti,'bonjour comment alfred',0)
        dump(ti,'bonjour comment alfred',1)

        # ---------- Vrai test
            
            
        words = set()
        
        ti = Dispatch('tstlib.TextIndex')
        from glob import glob
        start = clock()
        for input_filename in glob(r'..\..\textindex\*.txt')[0:2]:
            print input_filename
            for linenumber, line in enumerate(file(input_filename,'rb')):
                content = line.decode('iso-8859-1').lower()
                ti.AddText(content,input_filename) #"%s:%i"%(input_filename,linenumber))
                #for word in words_re.findall(content):
                #    words.add(word)
                #    ti.AddWord(word,"%s:%i"%(input_filename,linenumber))
        print 'Index construit en %.2f'%(clock()-start)
        print 'Saving...',
        ti.Save(r'..\..\textindex\complete.ti')
        print 'OK !'
        
        dump(ti,'b??j* sole*',0)

        ti = Dispatch('tstlib.TextIndex')
        print 'Loading...',
        ti.Load(r'..\..\textindex\complete.ti')
        print 'OK !'
        
        dump(ti,'b??j* sole*',0)
        
        print "Suppression de tous les documents"        
        for input_filename in glob(r'..\..\textindex\*.txt'):
            print input_filename
            ti.RemoveDocument(input_filename)
        print "Pack..."
        start = clock()
        ti.Pack()
        print 'Pack en %.2f'%(clock()-start)
        print "Enregistrement..."
        ti.Save(r'..\..\textindex\empty.ti')
    
        dump(ti,'b??j* sole*',0)
    except:
        traceback.print_exc()
finally:
    raw_input('Press enter...')
    

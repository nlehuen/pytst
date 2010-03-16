# -*- coding: iso-8859-1 -*-

import sys
# sys.path.insert(0,r"D:\projets\tst\python\Debug")

import unittest
import os
import random
import string
import datetime
from time import time
from itertools import izip

from tst import *

random.seed(0)

def random_string(length):
    return ''.join([random.choice(string.letters) for x in xrange(length)])

from timer import Timer
from distance import levenshtein

timers = {}

def timer_start(name):
    timers.setdefault(name,Timer()).start()

def timer_end(name,normalize=1.0):
    timers.setdefault(name,Timer()).stop(normalize)

def print_timers(comment):
    keys = timers.keys()
    keys.sort()

    for name in keys: 
        print '%16s : %s'%(name,timers[name])
    
    statsfilename = os.path.join(os.path.dirname(__file__),'stats.csv')
    if os.path.isfile(statsfilename):
        statsfile = file(statsfilename,'ab')
    else:
        statsfile = file(statsfilename,'wb')
        header = [
            'date',
            'version',
            'comment'
        ]
        for key in keys:
            header.append('%s:min'%key)
            header.append('%s:med'%key)
            header.append('%s:avg'%key)
            header.append('%s:max'%key)

        statsfile.write(';'.join(header))
        statsfile.write('\n')
    
    row = [
        datetime.datetime.now().strftime('%d/%m/%Y %H:%M:%S'),
        TST_VERSION,
        comment,
    ]
    for key in keys:
        timer = timers[key]
        row.append(('%7.4f'%timer.min).replace('.',','))
        row.append(('%7.4f'%timer.med).replace('.',','))
        row.append(('%7.4f'%timer.avg).replace('.',','))
        row.append(('%7.4f'%timer.max).replace('.',','))
    
    statsfile.write(';'.join(row))
    statsfile.write('\n')

class TestRefCount(unittest.TestCase):
    def setUp(self):
        self.a = 'toto'
        self.rc_a = sys.getrefcount(self.a)
        self.rc_None = sys.getrefcount(None)
        self.tree=TST()
        
    def testSetup(self):
        self.assertEqual(sys.getrefcount(None),self.rc_None+17)
        self.assertEqual(sys.getrefcount(self.a),self.rc_a)

    def testStore(self):
        self.tree[self.a]=self.a
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+1)
        
    def testOverwrite(self):
        self.tree[self.a]=self.a
        a2 = self.tree.put(self.a,'coucou')
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+1)
        del(a2)
        self.assertEqual(sys.getrefcount(self.a),self.rc_a)
    
    def testWalkList(self):
        l=self.tree.walk(None,ListAction())
        self.assertEqual(sys.getrefcount(self.a),self.rc_a)
        self.tree[self.a]=self.a
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+1)
        l=self.tree.walk(None,ListAction())
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+2)
        del(l)
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+1)

    def testWalkDict(self):
        self.tree[self.a]=self.a
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+1)
        d=self.tree.walk(None,DictAction())
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+2)
        del(d)
        self.assertEqual(sys.getrefcount(self.a),self.rc_a+1)
        del self.tree[self.a]
        self.assertEqual(sys.getrefcount(self.a),self.rc_a)
    
    def testRemove(self):
        del(self.tree)
        self.assertEqual(sys.getrefcount(None),self.rc_None)
        self.assertEqual(sys.getrefcount(self.a),self.rc_a)

class TestCollectors(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.keys = dict(
            a = 1,
            ab = 2,
            abc = 3,
            b = 4
        )
        for k,v in self.keys.iteritems():
            self.tree[k] = v
    
    def testListAction(self):
        l = self.tree.walk(None,ListAction())
        self.assertEqual(l,[1,2,3,4])
    
    def testTupleListAction(self):
        l = self.tree.walk(None,TupleListAction())
        self.assertEqual(l,[('a',0,1),('ab',0,2),('abc',0,3),('b',0,4)])

    def testDictAction(self):
        l = self.tree.walk(None,DictAction())
        self.assertEqual(l,dict(a=(0,1),ab=(0,2),abc=(0,3),b=(0,4)))

def skey():
    format = '%%.%if'%random.randint(1,10)
    return format%random.random()

class TestBasics(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.keys = dict([
            (skey(),random.random())
            for x in xrange(250)
        ])
        for k,v in self.keys.iteritems():
            self.tree[k] = v
        
    def testGet(self):
        for k,v in self.keys.iteritems():
            self.assertEqual(self.tree[k],v)

    def testWithRemove(self):
        for k in random.sample(self.keys,len(self.keys)/8):
            del self.keys[k]
            del self.tree[k]
        self.tree.pack()
        self.testGet()

    def testWithUpdate(self):
        for k in random.sample(self.keys,len(self.keys)/8):
            v = self.keys[k]
            nv = random.random()
            self.keys[k] = nv
            self.assertEqual(self.tree.put(k,nv),v)
        self.testGet()
        
    def testWalk(self):
        timer_start("walk")
        for i in xrange(100):
            d = self.tree.walk(None,DictAction())
        timer_end("walk")
        for k,v in d.iteritems():
            self.assertEquals(self.tree[k],v[1])        

    def testWalkWithRoot(self):
        ref = self.tree.walk(None,DictAction())

        timer_start("walk_root")
        for i in xrange(100):
            d = self.tree.walk(None,DictAction(),'0.1')
        timer_end("walk_root")
        for k, v in ref.iteritems():
            if k.startswith('0.1'):
                self.assert_(k in d)
                self.assertEquals(v,d[k])
        for k, v in d.iteritems():
            self.assert_(k.startswith('0.1'))
            self.assertEquals(self.tree[k],v[1])
    
    def testCloseMatch(self):
        for k1 in self.keys.iterkeys():
            timer_start("close_match")        
            d = self.tree.close_match(k1,4,None,DictAction())
            timer_end("close_match")
            for k2 in self.keys.iterkeys():
                distance = levenshtein(k1,k2)
                if distance<=4:
                    self.assert_(k2 in d,"Match manquant pour %s : %s (distance = %i)"%(
                        k1,
                        k2,
                        distance,
                    ))
                    self.assert_(k2 in d and d[k2][0]==distance,"Mauvaise distance pour %s et %s : %i != %s"%(
                        k1,
                        k2,
                        distance,
                        d.get(k2)[0]
                    ))
                else:
                    self.assert_(k2 not in d,"Mauvaise distance pour %s et %s : %i > 4 mais trouvé %s"%(
                        k1,
                        k2,
                        distance,
                        d.get(k2)
                    ))

    def testPrefixMatch(self):
        for k1 in self.keys.iterkeys():
            timer_start("prefix_match")        
            d = self.tree.prefix_match(k1[:len(k1)/2],None,DictAction())
            timer_end("prefix_match")
            self.assert_(k1 in d,"Une cle manque dans un prefix_match pour %s"%(k1,))
            k2 = k1 + k1
            timer_start("prefix_match")        
            d = self.tree.prefix_match(k2,None,DictAction())
            timer_end("prefix_match")
            self.assert_(k2 not in d,"Une cle manque dans un prefix_match pour %s"%(k1,))

    def testWriteRead(self):
        self.tree.write_to_file('test.tst')
        
        self.tree = TST()
        self.tree.read_from_file('test.tst')
        
        self.testGet()

class TestMatch(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.tree['abc'] = 'abc'
        self.tree['ab'] = 'ab'
        self.tree['a'] = 'a'
        self.tree['bbc'] = 'bbc'
        self.tree['efgfjhny'] = 'ok'
    
    def testJoker1(self):
        d = self.tree.match("a?c",None,DictAction())
        self.assertEquals(d,dict(abc=(0,"abc")))

    def testJoker2(self):
        d = self.tree.match("???",None,DictAction())
        self.assertEquals(d,{'abc': (0, 'abc'), 'bbc': (0, 'bbc')})

    def testJoker3(self):
        d = self.tree.match("??",None,DictAction())
        self.assertEquals(d,{'ab': (0, 'ab')})

    def testStar1(self):
        d = self.tree.match("a*c",None,DictAction())
        self.assertEquals(d,dict(abc=(0,"abc")))

    def testStar2(self):
        d = self.tree.match("a*",None,DictAction())
        self.assertEquals(d,{'a': (0, 'a'), 'ab': (0, 'ab'), 'abc': (0, 'abc')})

    def testStar2_1(self):
        d = self.tree.match("ab*",None,DictAction())
        self.assertEquals(d,{'ab': (0, 'ab'), 'abc': (0, 'abc')})

    def testStar2_2(self):
        d = self.tree.match("*b",None,DictAction())
        self.assertEquals(d,{'ab': (0, 'ab')})

        d = self.tree.match("*bbc",None,DictAction())
        self.assertEquals(d,{'bbc': (0, 'bbc')})

    def testStar3(self):
        d = self.tree.match("*",None,DictAction())
        self.assertEquals(d,{'a': (0, 'a'), 'ab': (0, 'ab'), 'bbc': (0, 'bbc'), 'abc': (0, 'abc'), 'efgfjhny': (0, 'ok')})

        d = self.tree.match("*?*",None,DictAction())
        self.assertEquals(d,{'a': (0, 'a'), 'ab': (0, 'ab'), 'bbc': (0, 'bbc'), 'abc': (0, 'abc'), 'efgfjhny': (0, 'ok')})

    def testStar3_1(self):
        d = self.tree.match("**",None,DictAction())
        self.assertEquals(d,{'a': (0, 'a'), 'ab': (0, 'ab'), 'bbc': (0, 'bbc'), 'abc': (0, 'abc'), 'efgfjhny': (0, 'ok')})

        d = self.tree.match("***",None,DictAction())
        self.assertEquals(d,{'a': (0, 'a'), 'ab': (0, 'ab'), 'bbc': (0, 'bbc'), 'abc': (0, 'abc'), 'efgfjhny': (0, 'ok')})

    def testStar4(self):
        d = self.tree.match("e*ny",None,DictAction())
        self.assertEquals(d,{'efgfjhny': (0, 'ok')})

    def testStar5(self):
        d = self.tree.match("*****y",None,DictAction())
        self.assertEquals(d,{'efgfjhny': (0, 'ok')})

    def testStar6(self):
        d = self.tree.match("????*",None,DictAction())
        self.assertEquals(d,{'efgfjhny': (0, 'ok')})

    def testStar7(self):
        d = self.tree.match("ef?f*n?",None,DictAction())
        self.assertEquals(d,{'efgfjhny': (0, 'ok')})

class TestIterators(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.keys = dict(
            titi = 1,
            toto = 2,
            tati = 3,
            a    = 5
        )
        for k, v in self.keys.iteritems():
            self.tree[k] = v
            
    def testLexical1(self):
        d = {}
        for k, v in self.tree:
            d[k] = v
        self.assertEqual(d,self.keys)
        
    def testLexical2(self):
        d = {}
        for k, v in self.tree.iterator('t'):
            d[k] = v
        self.keys.pop('a')
        self.assertEqual(d,self.keys)

    def testCloseMatch(self):
        d = {}
        for k, v in self.tree.close_match_iterator('t',1):
            d[k] = v
        self.assertEqual(d,dict(
            a = 5
        ))
        d = {}
        for k, v in self.tree.close_match_iterator('tito',1):
            d[k] = v
        self.assertEqual(d,dict(
            titi = 1,
            toto = 2
        ))
        d = {}
        for k, v in self.tree.close_match_iterator('tuto',1):
            d[k] = v
        self.assertEqual(d,dict(
            toto = 2
        ))

class TestCallableAction(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.tree['foo'] = 'bar'

    def testCA1(self):
        res = {}
    
        def callback(key, length, obj):
            res[key] = obj
        
        def result():
            res['hello'] = 'world'
            return res
        
        self.assertEqual(
            self.tree.walk(None, CallableAction(callback, result)),
            {'foo':'bar', 'hello':'world'}
        )

    def testCA2(self):
        res = {}
    
        def callback(key, length, obj):
            # Provoke an exception
            print 0 / 0
            res[key] = obj
        
        def result():
            return res
        
        try:
            self.tree.walk(None, CallableAction(callback, result)),
            self.fail("Should have raised an exception")
        except ZeroDivisionError:
            pass
        
    def testCA3(self):
        res = {}
    
        def callback(key, length, obj):
            res[key] = obj
        
        def result():
            # Provoke an exception
            return 0/0
        
        try:
            self.tree.walk(None, CallableAction(callback, result)),
            self.fail("Should have raised an exception")
        except ZeroDivisionError:
            pass

class TestCallableFilter(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.tree['foo'] = 'bar'
        self.tree['bar'] = 'foo'

    def testCF1(self):
        res = {}
    
        def cfilter(key, length, obj):
            res[key] = obj
            return obj
        
        self.tree.walk(CallableFilter(cfilter),None)
        
        self.assertEqual(
            res,
            {'foo':'bar', 'bar':'foo'}
        )

    def testCF2(self):
        def cfilter(key, length, obj):
            if key=='foo':
                return 'boo'
            else:
                return obj
        
        self.assertEqual(
            self.tree.walk(CallableFilter(cfilter),DictAction()),
            {'foo':(0,'boo'),'bar':(0,'foo')}
        )

    def testCF3(self):
        def cfilter(key, length, obj):
            if key=='foo':
                # raises an exception
                return 0 / 0
            else:
                return obj

        try:
            self.tree.walk(CallableFilter(cfilter),DictAction()),
            self.fail("Should have raised an exception")
        except ZeroDivisionError:
            pass

class TestHighCapacity(unittest.TestCase):
    def setUp(self):
        tree = TST()
        timer_start('build_big')
        keys = map(str,xrange(100000))
        random.shuffle(keys)
        timer_end('build_big')
        timer_start('write_big')
        for k in keys:
            tree[k] = k
        timer_end('write_big')

        self.keys, self.tree = keys, tree
    
    def testGet(self):
        timer_start('read_big')
        for k in self.keys:
            self.assertEqual(self.tree[k],k)
        timer_end('read_big')

    def testFullPack(self):
        timer_start('delete_full')
        for k in self.keys:
            del self.tree[k]
        timer_end('delete_full')
        
        self.tree.pack()

        for k in self.keys:
            self.assertEqual(self.tree[k],None)

        sample = random.sample(self.keys,len(self.keys)/10)
        random.shuffle(sample)
        timer_start('refill_post_pack/10')
        for k in sample:
            self.tree[k] = k
        timer_end('refill_post_pack/10',10)

        for k in sample:
            self.assertEqual(self.tree[k],k)
            del self.tree[k]
        
        self.tree.pack()

        for k in self.keys:
            self.assertEqual(self.tree[k],None)

        self.tree.write_to_file('test.tst')

    def testDelete(self):
        sample = random.sample(self.keys,len(self.keys)/10)
        
        random.shuffle(sample)
        timer_start('delete_big/10')
        for k in sample:
            del self.tree[k]
        timer_end('delete_big/10',10)

        random.shuffle(sample)
        timer_start('refill_pre_pack/10')
        for k in sample:
            self.tree[k] = k
        timer_end('refill_pre_pack/10',10)

        self.testGet()

        random.shuffle(sample)
        timer_start('delete_big/10')
        for k in sample:
            del self.tree[k]
        timer_end('delete_big/10',10)

        self.tree.pack()

        random.shuffle(sample)
        timer_start('refill_post_pack/10')
        for k in sample:
            self.tree[k] = k
        timer_end('refill_post_pack/10',10)

        self.testGet()

        timer_start('delete_big/10')
        for k in self.keys[:len(self.keys)/10]:
            del self.tree[k]
        timer_end('delete_big/10',10)

        timer_start('pack/10')
        self.tree.pack()
        timer_end('pack/10',10)

        timer_start('check_delete_big')
        for k in self.keys[:len(self.keys)/10]:
            self.assertEqual(self.tree[k],None)
        for k in self.keys[len(self.keys)/10+1:]:
            self.assertEqual(self.tree[k],k)
        timer_end('check_delete_big')

    def testUpdate(self):
        timer_start('build_big/10')
        old_keys = self.keys[:len(self.keys)/10]
        new_keys = map(lambda x:str(int(x) + 1),old_keys) 
        timer_end('build_big/10',10)
        timer_start('update_big/10')
        for k,kp in izip(old_keys,new_keys):
            self.assertEqual(self.tree.put(k,kp),k)
        timer_end('update_big/10',10)
        timer_start('check_update_big')
        for k,kp in izip(old_keys,new_keys):
            self.assertEqual(self.tree[k],kp)
        timer_end('check_update_big')

class TestScan(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.tree['Nicolas']='Nicolas'
        self.tree['olaf']='olaf'
        self.tree['lazlo']='lazlo'
        self.tree['Nicolas-Antoinette']='Nicolas-Antoinette'
        self.tree['Antoinette']='Antoinette'
        self.tree['Antoine']='Antoine'
        self.tree['astride']='astride'
        self.tree['VICTOIRE']='VICTOIRE'
        self.tree['IAN']='IAN'
        self.tree['x']='x'
        self.tree['V']='V'
        self.tree['ROBERT']='ROBERT'
        self.tree['A N']='A N'
        self.tree['olaaf']='olaaf'
        self.tree['laslo']='laslo'

    def testScanMikeThornton(self):
        t = TST()
        t['ccc'] = 1
        self.assertEqual(t.scan('cc',TupleListAction()),[('cc',-2,None)])
        self.assertEqual(t.scan('ccd',TupleListAction()),[('ccd',-3,None)])

    def testScan0_1(self):
        self.assertEqual(self.tree.scan('Nicolas',TupleListAction()),[('Nicolas', 7, 'Nicolas'),])
    
    def testScan0_2(self):
        self.assertEqual(self.tree.scan(' Nicolas',TupleListAction()),[(' ',-1,None),('Nicolas', 7, 'Nicolas'),])
    
    def testScan0_3(self):
        self.assertEqual(self.tree.scan('Nicolas ',TupleListAction()),[('Nicolas', 7, 'Nicolas'),(' ',-1,None),])
    
    def testScan0_4(self):
        self.assertEqual(self.tree.scan(' Nicolas ',TupleListAction()),[(' ',-1,None),('Nicolas', 7, 'Nicolas'),(' ',-1,None),])
    
    def testScan0_5(self):
        self.assertEqual(self.tree.scan(' ',TupleListAction()),[(' ',-1,None),])
    
    def testScan0_6(self):
        self.assertEqual(self.tree.scan('la',TupleListAction()),[('la', -2, None)])
    
    def testScan0_7(self):
        self.assertEqual(self.tree.scan('lazl',TupleListAction()),[('lazl', -4, None)])
    
    def testScan1(self):
        timer_start("scan")
        for i in xrange(10000):
            self.assertEqual(self.tree.scan('lazlo',TupleListAction()),[('lazlo', 5, 'lazlo')])
            self.assertEqual(self.tree.scan('Nicolazlo',TupleListAction()),[('Nico', -4, None), ('lazlo', 5, 'lazlo')])
        timer_end("scan")
    
    def testScan24(self):
        self.assertEqual(self.tree.scan('A NicoNicoNicolasNicoNico',TupleListAction()),[('A N', 3, 'A N'), ('icoNico', -7, None), ('Nicolas', 7, 'Nicolas'), ('NicoNico', -8, None)])
    
    def testScan1_1(self):
        self.assertEqual(self.tree.scan('hippocampe',TupleListAction()),[('hippocampe', -10, None)])
    
    def testScan2(self):
        self.assertEqual(self.tree.scan('NicolaNicolaNicolaNicolaNicola',TupleListAction()),[('NicolaNicolaNicolaNicolaNicola', -30, None)])
    
    def testScan3(self):
        self.assertEqual(self.tree.scan('Nicolasstupide',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('stupide', -7, None)])
    
    def testScan4(self):
        self.assertEqual(self.tree.scan('Nicolast',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('t', -1, None)])
    
    def testScan5(self):
        self.assertEqual(self.tree.scan('xxxNicolas',TupleListAction()),[('x', 1, 'x'), ('x', 1, 'x'), ('x', 1, 'x'), ('Nicolas', 7, 'Nicolas')])
    
    def testScan6(self):
        self.assertEqual(self.tree.scan('xxx Nicolas',TupleListAction()),[('x', 1, 'x'), ('x', 1, 'x'), ('x', 1, 'x'), (' ', -1, None), ('Nicolas', 7, 'Nicolas')])
    
    def testScan7(self):
        self.assertEqual(self.tree.scan('Antoinette Antoinette',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])
    
    def testScan8(self):
        self.assertEqual(self.tree.scan('Nicolas-Antoinette',TupleListAction()),[('Nicolas-Antoinette', 18, 'Nicolas-Antoinette')])
    
    def testScan9(self):
        self.assertEqual(self.tree.scan('Nicolas-Antoine',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
    
    def testScan9_1(self):
        self.assertEqual(self.tree.scan('Nicolas-Antoine-Antoine',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
    
    def testScan9_2(self):
        self.assertEqual(self.tree.scan('Nicolas-Antoine-Antoine-',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('-', -1, None)])
    
    def testScan10(self):
        self.assertEqual(self.tree.scan('Nicolas-Antoinet',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('t', -1, None)])
    
    def testScanWithStopChars1(self):
        self.assertEqual(self.tree.scan_with_stop_chars('Nicolas',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas')])
    
    def testScanWithStopChars2(self):
        self.assertEqual(self.tree.scan_with_stop_chars('Nicolasstupide',' -',TupleListAction()),[('Nicolasstupide', -14, None)])
    
    def testScanWithStopChars25(self):
        timer_start("scan_stop_chars")
        for i in xrange(10000):
            self.assertEqual(self.tree.scan_with_stop_chars('A Nico trlalaA Nico Nico Nico Nicolas Nico Nicol Nicol Nico',' ',TupleListAction()),[('A Nico trlalaA Nico Nico Nico ', -30, None), ('Nicolas', 7, 'Nicolas'), (' Nico Nicol Nicol Nico', -22, None)])
            self.assertEqual(self.tree.scan_with_stop_chars('A Nico trlalaA Nico Nico Nico Nicolas Nico Nicol Nicol Nico',' ',TupleListAction()),[('A Nico trlalaA Nico Nico Nico ', -30, None), ('Nicolas', 7, 'Nicolas'), (' Nico Nicol Nicol Nico', -22, None)])
            self.assertEqual(self.tree.scan_with_stop_chars('A Nico trlalaA Nico Nico Nico Nicolas Nico Nicol Nicol Nico',' ',TupleListAction()),[('A Nico trlalaA Nico Nico Nico ', -30, None), ('Nicolas', 7, 'Nicolas'), (' Nico Nicol Nicol Nico', -22, None)])
        timer_end("scan_stop_chars")

    def testScanWithStopChars3(self):
        self.assertEqual(self.tree.scan_with_stop_chars('Nicolast',' -',TupleListAction()),[('Nicolast', -8, None)])
    
    def testScanWithStopChars4(self):
        self.assertEqual(self.tree.scan_with_stop_chars('xxxNicolas',' -',TupleListAction()),[('xxxNicolas', -10, None)])
    
    def testScanWithStopChars5(self):
        self.assertEqual(self.tree.scan_with_stop_chars('xxx Nicolas',' -',TupleListAction()),[('xxx ', -4, None),('Nicolas', 7, 'Nicolas')])
    
    def testScanWithStopChars6(self):
        self.assertEqual(self.tree.scan_with_stop_chars('xxxAntoine Nicolas',' -',TupleListAction()),[('xxxAntoine ', -11, None),('Nicolas', 7, 'Nicolas')])
    
    def testScanWithStopChars8(self):
        self.assertEqual(self.tree.scan_with_stop_chars('Nicolas-Antoinette',' -',TupleListAction()),[('Nicolas-Antoinette', 18, 'Nicolas-Antoinette')])
    
    def testScanWithStopChars9(self):
        self.assertEqual(self.tree.scan_with_stop_chars('Nicolas-Antoine',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
    
    def testScanWithStopChars10(self):
        self.assertEqual(self.tree.scan_with_stop_chars('Nicolas-Antoinet',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-Antoinet', -9, None)])
    
    def testScanVicieux(self):
        self.assertEqual(self.tree.scan_with_stop_chars('xxxAntoine A Nicolas',' -',TupleListAction()),[('xxxAntoine A ', -13, None),('Nicolas', 7, 'Nicolas')])
    
    def testScanVicieux2(self):
        self.assertEqual(self.tree.scan_with_stop_chars('Antoinette Antoinette',' -',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])
    
    def testScanVicieux3(self):
        self.assertEqual(self.tree.scan_with_stop_chars('nastride lazlo',' -',TupleListAction()),[('nastride ', -9, None), ('lazlo', 5, 'lazlo')])
        self.assertEqual(self.tree.scan_with_stop_chars('VIAN ROBERT',' -',TupleListAction()),[('VIAN ', -5, None), ('ROBERT', 6, 'ROBERT')])

    def testScanKeithDavidson1(self):
        t = TST()
        t['333'] = 'ccc'
        # self.assertEqual(t.scan('.33.',TupleListAction()),[('.33.',-4,None)])
        self.assertEqual(t.scan('.33333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('33.',-3,None)])

    def testScanKeithDavidson2(self):
        t = TST()
        t['333'] = 'ccc'
        self.assertEqual(t.scan('.33.',TupleListAction()),[('.33.',-4,None)])
        self.assertEqual(t.scan('.33333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('33.',-3,None)])

    def testScanKeithDavidson2_1(self):
        t = TST()
        t['333'] = 'ccc'
        self.assertEqual(t.scan('.33333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('33.',-3,None)])
        self.assertEqual(t.scan('.33.',TupleListAction()),[('.33.',-4,None)])

    def testScanKeithDavidson3(self):
        t = TST()
        t['333'] = 'ccc'
        self.assertEqual(t.scan('.33333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('33.',-3,None)])
        self.assertEqual(t.scan('.3.',TupleListAction()),[('.3.',-3,None)])
        self.assertEqual(t.scan('.33.',TupleListAction()),[('.33.',-4,None)])
        self.assertEqual(t.scan('.333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('.',-1,None)])
        self.assertEqual(t.scan('.33333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('33.',-3,None)])

    def testScanKeithDavidson4(self):
        t = TST()
        t['3333'] = 'ccc'
        # self.assertEqual(t.scan('.333.',TupleListAction()),[('.333.',-5,None)])
        self.assertEqual(t.scan('.333333.',TupleListAction()),[('.',-1,None),('3333',4,'ccc'),('33.',-3,None)])

    def testScanKeithDavidson5(self):
        t = TST()
        t['3333'] = 'ccc'
        self.assertEqual(t.scan('.333.',TupleListAction()),[('.333.',-5,None)])
        self.assertEqual(t.scan('.333333.',TupleListAction()),[('.',-1,None),('3333',4,'ccc'),('33.',-3,None)])

    def testScanKeithDavidson6(self):
        t = TST()
        t['333'] = 'ccc'
        self.assertEqual(t.scan('.333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('.',-1,None)])
        self.assertEqual(t.scan('.333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('.',-1,None)])

    def testScanKeithDavidson7(self):
        t = TST()
        t['333'] = 'ccc'
        self.assertEqual(t.scan('.3.',TupleListAction()),[('.3.',-3,None)])
        self.assertEqual(t.scan('.333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('.',-1,None)])
        self.assertEqual(t.scan('.33333.',TupleListAction()),[('.',-1,None),('333',3,'ccc'),('33.',-3,None)])
        
class TestNewScan(unittest.TestCase):
  def setUp(self):
    self.tree = TST()
    self.tree['333'] = 'A'
    self.tree['334'] = 'B'
    self.tree['3333'] = 'C'
    self.tree['33378'] = 'D'
    self.tree['3339993339'] = 'E'
    
  def testA(self):
    self.assertEqual(self.tree.scan('3',TupleListAction()),[('3',-1,None)])
    self.assertEqual(self.tree.scan('33',TupleListAction()),[('33',-2,None)])
    self.assertEqual(self.tree.scan('3333',TupleListAction()),[('3333',4,'C')])

  def testB(self):
    self.assertEqual(self.tree.scan('',TupleListAction()),[])
    self.assertEqual(self.tree.scan('coucou',TupleListAction()),[('coucou',-6,None)])

  def testC(self):
    self.assertEqual(self.tree.scan('3337',TupleListAction()),[('333',3,'A'),('7',-1,None)])
    self.assertEqual(self.tree.scan('23337',TupleListAction()),[('2',-1,None),('333',3,'A'),('7',-1,None)])
    
  def testD(self):
    self.assertEqual(self.tree.scan('333',TupleListAction()),[('333',3,'A')])
    self.assertEqual(self.tree.scan('3333',TupleListAction()),[('3333',4,'C')])
    self.assertEqual(self.tree.scan('33378',TupleListAction()),[('33378',5,'D')])
    self.assertEqual(self.tree.scan('0333',TupleListAction()),[('0',-1,None),('333',3,'A')])
    self.assertEqual(self.tree.scan('335333',TupleListAction()),[('335',-3,None),('333',3,'A')])
  
  def testE(self):
    self.assertEqual(self.tree.scan('34',TupleListAction()),[('34',-2,None)])
    self.assertEqual(self.tree.scan('335',TupleListAction()),[('335',-3,None)])
    self.assertEqual(self.tree.scan('2335',TupleListAction()),[('2335',-4,None)])
    self.assertEqual(self.tree.scan('33332335',TupleListAction()),[('3333',4,'C'),('2335',-4,None)])

  def testF(self):
    self.assertEqual(self.tree.scan('3339993339',TupleListAction()),[('3339993339',10,'E')])
    self.assertEqual(self.tree.scan('333999333',TupleListAction()),[('333',3,'A'),('999',-3,None),('333',3,'A')])
    self.assertEqual(self.tree.scan('3339993333',TupleListAction()),[('333',3,'A'),('999',-3,None),('3333',4,'C')])
    self.assertEqual(self.tree.scan('3339993338',TupleListAction()),[('333',3,'A'),('999',-3,None),('333',3,'A'),('8',-1,None)])

if __name__ == '__main__':
    print "Testing pytst %s"%TST_VERSION

    comment = ' '.join(sys.argv[1:])

    suite = unittest.TestSuite((
        unittest.makeSuite(TestCollectors),
        unittest.makeSuite(TestBasics),
        unittest.makeSuite(TestHighCapacity),
        unittest.makeSuite(TestScan),
        unittest.makeSuite(TestNewScan),
        unittest.makeSuite(TestIterators),
        unittest.makeSuite(TestMatch),
        unittest.makeSuite(TestCallableAction),
        unittest.makeSuite(TestCallableFilter),
    ))
    
    for i in xrange(3):
        unittest.TextTestRunner().run(suite)

    print_timers(comment)

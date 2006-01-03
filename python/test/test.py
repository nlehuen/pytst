# -*- coding: iso-8859-1 -*-

import unittest
import sys
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

from tcc.timer import Timer
from tcc.util import levenshtein

timers = {}

def timer_start(name):
    timers.setdefault(name,Timer()).start()

def timer_end(name,normalize=1.0):
    timers.setdefault(name,Timer()).stop(normalize)

def print_timers(comment):
    keys = sorted(timers.keys())

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

class TestBasics(unittest.TestCase):
    def setUp(self):
        self.tree = TST()
        self.keys = dict([
            (str(random.random()),random.random())
            for x in xrange(4000)
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
        timer_start("walk_root")
        for i in xrange(100):
            d = self.tree.walk(None,DictAction(),'0.1')
        timer_end("walk_root")
        for k, v in d.iteritems():
            self.assertTrue(k.startswith('0.'))
            self.assertEquals(self.tree[k],v[1])
    
    def testCloseMatch(self):
        value = self.keys.keys()[0]
        timer_start("close_match")
        for i in xrange(100):
            d = self.tree.close_match(value,4,None,DictAction())
        timer_end("close_match")
        for k, v in d.iteritems():
            self.assertEqual(levenshtein(k,value),v[0])
    
    def testWriteRead(self):
        f = file('test.tst','wb')
        self.tree.write_to_file(f)
        f.close()
        
        f = file('test.tst','rb')
        self.tree = TST()
        self.tree.read_from_file(f)
        f.close()
        
        self.testGet()

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

    def testDelete(self):
        timer_start('delete_big/10')
        for k in self.keys[:len(self.keys)/10]:
            del self.tree[k]
        timer_end('delete_big/10',10)
        self.tree.pack()
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

if __name__ == '__main__':
    comment = ' '.join(sys.argv[1:])

    suite = unittest.TestSuite((
        unittest.makeSuite(TestCollectors),
        unittest.makeSuite(TestBasics),
        unittest.makeSuite(TestHighCapacity),
        unittest.makeSuite(TestScan),
     ))
    
    for i in xrange(3):
        unittest.TextTestRunner().run(suite)

    print_timers(comment)

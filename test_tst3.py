if __name__=='__main__':
    from tcc.tst import *
    import unittest

    class TestScan(unittest.TestCase):
        def setUp(self):
            self.t = TST()
            self.t['Nicolas']='Nicolas'
            self.t['olaf']='olaf'
            self.t['lazlo']='lazlo'
            self.t['Nicolas-Antoinette']='Nicolas-Antoinette'
            self.t['Antoinette']='Antoinette'
            self.t['Antoine']='Antoine'
            self.t['astride']='astride'
            self.t['VICTOIRE']='VICTOIRE'
            self.t['IAN']='IAN'
            self.t['x']='x'
            self.t['V']='V'
            self.t['ROBERT']='ROBERT'
            self.t['A N']='A N'
            self.t['olaaf']='olaaf'
            self.t['laslo']='laslo'

        def testRoot(self):
            self.t.debug_print_root()

        def testScan0_1(self):
            self.assertEqual(self.t.scan('Nicolas',TupleListAction()),[('Nicolas', 7, 'Nicolas'),])
        
        def testScan0_2(self):
            self.assertEqual(self.t.scan(' Nicolas',TupleListAction()),[(' ',-1,None),('Nicolas', 7, 'Nicolas'),])
        
        def testScan0_3(self):
            self.assertEqual(self.t.scan('Nicolas ',TupleListAction()),[('Nicolas', 7, 'Nicolas'),(' ',-1,None),])
        
        def testScan0_4(self):
            self.assertEqual(self.t.scan(' Nicolas ',TupleListAction()),[(' ',-1,None),('Nicolas', 7, 'Nicolas'),(' ',-1,None),])
        
        def testScan0_5(self):
            self.assertEqual(self.t.scan(' ',TupleListAction()),[(' ',-1,None),])
        
        def testScan0_6(self):
            self.assertEqual(self.t.scan('la',TupleListAction()),[('la', -2, None)])
        
        def testScan0_7(self):
            self.assertEqual(self.t.scan('lazl',TupleListAction()),[('lazl', -4, None)])
        
        def testScan1(self):
            self.assertEqual(self.t.scan('lazlo',TupleListAction()),[('lazlo', 5, 'lazlo')])
            self.assertEqual(self.t.scan('Nicolazlo',TupleListAction()),[('Nico', -4, None), ('lazlo', 5, 'lazlo')])
        
        def testScan24(self):
            self.assertEqual(self.t.scan('A NicoNicoNicolasNicoNico',TupleListAction()),[('A N', 3, 'A N'), ('icoNico', -7, None), ('Nicolas', 7, 'Nicolas'), ('NicoNico', -8, None)])
        
        def testScan1_1(self):
            self.assertEqual(self.t.scan('hippocampe',TupleListAction()),[('hippocampe', -10, None)])
        
        def testScan2(self):
            self.assertEqual(self.t.scan('NicolaNicolaNicolaNicolaNicola',TupleListAction()),[('NicolaNicolaNicolaNicolaNicola', -30, None)])

        def testScan25(self):
            self.assertEqual(self.t.scan_with_stop_chars('A Nico trlalaA Nico Nico Nico Nicolas Nico Nicol Nicol Nico',' ',TupleListAction()),[('A Nico trlalaA Nico Nico Nico ', -30, None), ('Nicolas', 7, 'Nicolas'), (' Nico Nicol Nicol Nico', -22, None)])
            self.assertEqual(self.t.scan_with_stop_chars('A Nico trlalaA Nico Nico Nico Nicolas Nico Nicol Nicol Nico',' ',TupleListAction()),[('A Nico trlalaA Nico Nico Nico ', -30, None), ('Nicolas', 7, 'Nicolas'), (' Nico Nicol Nicol Nico', -22, None)])
            self.assertEqual(self.t.scan_with_stop_chars('A Nico trlalaA Nico Nico Nico Nicolas Nico Nicol Nicol Nico',' ',TupleListAction()),[('A Nico trlalaA Nico Nico Nico ', -30, None), ('Nicolas', 7, 'Nicolas'), (' Nico Nicol Nicol Nico', -22, None)])
        
        def testScan3(self):
            self.assertEqual(self.t.scan('Nicolasstupide',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('stupide', -7, None)])
        
        def testScan4(self):
            self.assertEqual(self.t.scan('Nicolast',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('t', -1, None)])
        
        def testScan5(self):
            self.assertEqual(self.t.scan('xxxNicolas',TupleListAction()),[('x', 1, 'x'), ('x', 1, 'x'), ('x', 1, 'x'), ('Nicolas', 7, 'Nicolas')])
        
        def testScan6(self):
            self.assertEqual(self.t.scan('xxx Nicolas',TupleListAction()),[('x', 1, 'x'), ('x', 1, 'x'), ('x', 1, 'x'), (' ', -1, None), ('Nicolas', 7, 'Nicolas')])
        
        def testScan7(self):
            self.assertEqual(self.t.scan('Antoinette Antoinette',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])
        
        def testScan8(self):
            self.assertEqual(self.t.scan('Nicolas-Antoinette',TupleListAction()),[('Nicolas-Antoinette', 18, 'Nicolas-Antoinette')])
        
        def testScan9(self):
            self.assertEqual(self.t.scan('Nicolas-Antoine',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
        
        def testScan9_1(self):
            self.assertEqual(self.t.scan('Nicolas-Antoine-Antoine',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
        
        def testScan9_2(self):
            self.assertEqual(self.t.scan('Nicolas-Antoine-Antoine-',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('-', -1, None)])
        
        def testScan10(self):
            self.assertEqual(self.t.scan('Nicolas-Antoinet',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('t', -1, None)])
        
        def testScanWithStopChars1(self):
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas')])
        
        def testScanWithStopChars2(self):
            self.assertEqual(self.t.scan_with_stop_chars('Nicolasstupide',' -',TupleListAction()),[('Nicolasstupide', -14, None)])
        
        def testScanWithStopChars3(self):
            self.assertEqual(self.t.scan_with_stop_chars('Nicolast',' -',TupleListAction()),[('Nicolast', -8, None)])
        
        def testScanWithStopChars4(self):
            self.assertEqual(self.t.scan_with_stop_chars('xxxNicolas',' -',TupleListAction()),[('xxxNicolas', -10, None)])
        
        def testScanWithStopChars5(self):
            self.assertEqual(self.t.scan_with_stop_chars('xxx Nicolas',' -',TupleListAction()),[('xxx ', -4, None),('Nicolas', 7, 'Nicolas')])
        
        def testScanWithStopChars6(self):
            self.assertEqual(self.t.scan_with_stop_chars('xxxAntoine Nicolas',' -',TupleListAction()),[('xxxAntoine ', -11, None),('Nicolas', 7, 'Nicolas')])
        
        def testScanWithStopChars7(self):
            self.assertEqual(self.t.scan_with_stop_chars('xxxAntoine A Nicolas',' -',TupleListAction()),[('xxxAntoine A ', -13, None),('Nicolas', 7, 'Nicolas')])
        
        def testScanWithStopChars8(self):
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas-Antoinette',' -',TupleListAction()),[('Nicolas-Antoinette', 18, 'Nicolas-Antoinette')])
        
        def testScanWithStopChars9(self):
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas-Antoine',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
        
        def testScanWithStopChars10(self):
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas-Antoinet',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-Antoinet', -9, None)])
        
        def testScanVicieux(self):
            self.assertEqual(self.t.scan_with_stop_chars('xxxAntoine A Nicolas',' -',TupleListAction()),[('xxxAntoine A ', -13, None),('Nicolas', 7, 'Nicolas')])
        
        def testScanVicieux2(self):
            self.assertEqual(self.t.scan_with_stop_chars('Antoinette Antoinette',' -',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])
        
        def testScanVicieux3(self):
            self.assertEqual(self.t.scan_with_stop_chars('nastride lazlo',' -',TupleListAction()),[('nastride ', -9, None), ('lazlo', 5, 'lazlo')])
            self.assertEqual(self.t.scan_with_stop_chars('VIAN ROBERT',' -',TupleListAction()),[('VIAN ', -5, None), ('ROBERT', 6, 'ROBERT')])

    unittest.main()



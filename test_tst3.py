if __name__=='__main__':
    from tcc.tst import *
    import unittest

    class TestScan(unittest.TestCase):
        def setUp(self):
            self.t = TST()
            self.t['Nicolas']='Nicolas'
            self.t['Nicolas-Antoinette']='Nicolas-Antoinette'
            self.t['Antoinette']='Antoinette'
            self.t['Antoine']='Antoine'
            self.t['astride']='astride'
            self.t['x']='x'
            self.t['A N']='A N'
    
        def __testScan(self):
            self.assertEqual(self.t.scan('Nicolas',TupleListAction()),[('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan('Nicolasstupide',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('stupide', -7, None)])
            self.assertEqual(self.t.scan('Nicolast',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('t', -1, None)])
            self.assertEqual(self.t.scan('xxxNicolas',TupleListAction()),[('xxx', -3, None),('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan('xxx Nicolas',TupleListAction()),[('xxx ', -4, None),('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan('Antoinette Antoinette',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])
            self.assertEqual(self.t.scan('Nicolas-Antoinette',TupleListAction()),[('Nicolas-Antoinette', 18, 'Nicolas-Antoinette')])
            self.assertEqual(self.t.scan('Nicolas-Antoine',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
            self.assertEqual(self.t.scan('Nicolas-Antoinet',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('t', -1, None)])
    
        def __testScanWithStopChars(self):
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan_with_stop_chars('Nicolasstupide',' -',TupleListAction()),[('Nicolasstupide', -14, None)])
            self.assertEqual(self.t.scan_with_stop_chars('Nicolast',' -',TupleListAction()),[('Nicolast', -8, None)])
            self.assertEqual(self.t.scan_with_stop_chars('xxxNicolas',' -',TupleListAction()),[('xxxNicolas', -10, None)])
            self.assertEqual(self.t.scan_with_stop_chars('xxx Nicolas',' -',TupleListAction()),[('xxx ', -4, None),('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan_with_stop_chars('xxxAntoine Nicolas',' -',TupleListAction()),[('xxxAntoine ', -11, None),('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan_with_stop_chars('xxxAntoine A Nicolas',' -',TupleListAction()),[('xxxAntoine A ', -13, None),('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas-Antoinette',' -',TupleListAction()),[('Nicolas-Antoinette', 18, 'Nicolas-Antoinette')])
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas-Antoine',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
            self.assertEqual(self.t.scan_with_stop_chars('Nicolas-Antoinet',' -',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-Antoinet', -9, None)])

        def testScanVicieux(self):
            self.assertEqual(self.t.scan_with_stop_chars('xxxAntoine A Nicolas',' -',TupleListAction()),[('xxxAntoine A ', -13, None),('Nicolas', 7, 'Nicolas')])

        def testScanVicieux2(self):
            print '-------'
            self.assertEqual(self.t.scan_with_stop_chars('Antoinette Antoinette',' -',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])

    unittest.main()
    


if __name__=='__main__':
    from tcc.tst import *
    import unittest

    class TestScan(unittest.TestCase):
        def setUp(self):
            self.t = TST()
            self.t['Nicolas']='Nicolas'
            self.t['lazlo']='laszlo'
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

        def testScan(self):
            self.assertEqual(self.t.scan('Nicolazlo',TupleListAction()),[('Nico', -4, None), ('lazlo', 5, 'laszlo')])
            self.assertEqual(self.t.scan('Nicolas',TupleListAction()),[('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan('Nicolasstupide',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('stupide', -7, None)])
            self.assertEqual(self.t.scan('Nicolast',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('t', -1, None)])
            self.assertEqual(self.t.scan('xxxNicolas',TupleListAction()),[('x', 1, 'x'), ('x', 1, 'x'), ('x', 1, 'x'), ('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan('xxx Nicolas',TupleListAction()),[('x', 1, 'x'), ('x', 1, 'x'), ('x', 1, 'x'), (' ', -1, None), ('Nicolas', 7, 'Nicolas')])
            self.assertEqual(self.t.scan('Antoinette Antoinette',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])
            self.assertEqual(self.t.scan('Nicolas-Antoinette',TupleListAction()),[('Nicolas-Antoinette', 18, 'Nicolas-Antoinette')])
            self.assertEqual(self.t.scan('Nicolas-Antoine',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine')])
            self.assertEqual(self.t.scan('Nicolas-Antoinet',TupleListAction()),[('Nicolas', 7, 'Nicolas'), ('-', -1, None), ('Antoine', 7, 'Antoine'), ('t', -1, None)])

        def testScanWithStopChars(self):
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
            self.assertEqual(self.t.scan_with_stop_chars('Antoinette Antoinette',' -',TupleListAction()),[('Antoinette', 10, 'Antoinette'), (' ', -1, None), ('Antoinette', 10, 'Antoinette')])

        def testScanVicieux3(self):
            self.assertEqual(self.t.scan_with_stop_chars('nastride lazlo',' -',TupleListAction()),[('nastride ', -9, None), ('lazlo', 5, 'laszlo')])
            self.assertEqual(self.t.scan_with_stop_chars('VIAN ROBERT',' -',TupleListAction()),[('VIAN ', -5, None), ('ROBERT', 6, 'ROBERT')])

    unittest.main()



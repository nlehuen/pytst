from win32com.client.gencache import EnsureDispatch as Dispatch
from win32com.client import Dispatch
import traceback

try:
	try:
		ti = Dispatch('tstlib.TextIndex')

		print "Version :",ti.Version

		ti.AddText('bonjour, je suis nicolas','1')
		ti.AddText('bonjour, je suis alfred','2')
		ti.AddText('alfred hitchcock','3')
		ti.AddText('bonjour comment allez-vous ?','3')

		result = ti.FindWord('bonjour')
		for i in range(result.Size):
			print result.GetDocument(i), result.GetScore(i)
		
		print
		
		result = ti.FindTextA('bonjour comment alfred',0)
		for i in range(result.Size):
			print result.GetDocument(i), result.GetScore(i)
			
		print "Saved %s !"%ti.Save(r'c:\temp\test.ti')

		ti = Dispatch('tstlib.TextIndex')
		print "Loaded %s !"%ti.Load(r'c:\temp\test.ti')

		print
		
		result = ti.FindTextA('bonjour comment alfred',0)
		for i in range(result.Size):
			print result.GetDocument(i), result.GetScore(i)
			
		ti = Dispatch('tstlib.TextIndex')
		from glob import glob
		for input_filename in glob(r'D:\projets\tst\textindex\*.txt'):
			print input_filename
			for linenumber, line in enumerate(file(input_filename,'rb')):
				content = line.decode('iso-8859-1')
				ti.AddText(content,"%s:%i"%(input_filename,linenumber))
		print 'Saving...',
		ti.Save(r'D:\projets\tst\textindex\complete.ti')
		print 'OK !'
		
		ti = Dispatch('tstlib.TextIndex')
		print 'Loading...',
		ti.Load(r'D:\projets\tst\textindex\complete.ti')
		print 'OK !'
		result = ti.FindTextA('bonj sole',0)
		for i in range(result.Size):
			print result.GetDocument(i), result.GetScore(i)
	except:
		traceback.print_exc()
finally:
	raw_input('Press enter...')
	

from win32com.client.gencache import EnsureDispatch as Dispatch
from win32com.client import Dispatch
import traceback

try:
	try:
		ti = Dispatch('tstlib.TextIndex')

		print "Version :",ti.Version

		ti.AddText('bonjour, je suis nicolas','1')
		ti.AddText('bonjour, je suis alfred','2')
		ti.AddText('bonjour comment allez-vous ?','3')

		result = ti.FindWord('bonjour')
		for i in range(result.Size+1):
			print result.GetDocument(i), result.GetScore(i)
		
		print
		
		result = ti.FindTextA('bonjour comment alfred',0)
		for i in range(result.Size+1):
			print result.GetDocument(i), result.GetScore(i)
	except:
		traceback.print_exc()
finally:
	raw_input('Press enter...')
	
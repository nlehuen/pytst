from win32com.client.gencache import EnsureDispatch as Dispatch
from win32com.client import Dispatch
import traceback

try:
	try:
		ti = Dispatch('tstlib.TextIndex')

		print "Version :",ti.Version

		ti.AddText('bonjour, je suis nicolas','1')
		ti.AddText('bonjour, je suis alfred','2')
		ti.AddText('bonjour comment allez-vous ?','1')

		ti.FindWord('bonjour')
		ti.FindTextA('bonjour comment',0)
	except:
		traceback.print_exc()
finally:
	raw_input('Press enter...')
	
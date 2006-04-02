import tst
import zipfile

z = zipfile.ZipFile('pytst-%s-win32-py2.4.zip'%tst.TST_VERSION.lower(),'w',zipfile.ZIP_DEFLATED)
z.write('boost_python.dll')
z.write('tst.pyd')
z.close()

copy boost_python.dll ..\test
copy tst.pyd ..\test
..\test\test.py %*
del ..\test\tst.pyd 

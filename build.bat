swig -c++ -python tst.i
python setup.py clean install
copy build\lib.win32-2.4\*.* ..\python\tcc

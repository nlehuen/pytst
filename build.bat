swig -c++ -python tst.i
python setup.py clean build --compile=mingw32
copy build\lib.win32-2.3\*.* ..\python\tcc

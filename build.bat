rmdir /s /q build dist
swig -c++ -python tst.i
python setup.py clean install sdist bdist_wininst
copy build\lib.win32-2.4\*.* ..\python\tcc

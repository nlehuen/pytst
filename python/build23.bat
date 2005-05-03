rmdir /s /q build include
mkdir include & xcopy ..\include include
swig -Iinclude -c++ -python tst.i
c:\python23\python setup.py clean build --compile=mingw32 install sdist bdist_wininst
rmdir /s /q build include

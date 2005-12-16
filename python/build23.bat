rmdir /s /q build include
mkdir include & xcopy ..\include include
swig -Iinclude -DSCANNER -c++ -python tst.i
C:\python23\python setup.py clean build --compile=mingw32 install sdist bdist_egg bdist_wininst
rmdir /s /q build include

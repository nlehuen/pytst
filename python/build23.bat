rmdir /s /q build include
mkdir include & xcopy ..\include include
swig -O -Iinclude -DSCANNER -c++ -python tst.i
c:\python23\python setup.py clean build --compile=mingw32 sdist bdist_wininst
rmdir /s /q build include

rmdir /s /q build include
mkdir include & xcopy ..\include include
copy ..\include\LICENSE .
swig -O -Iinclude -DSCANNER -c++ -python tst.i
del MANIFEST
python setup.py clean sdist bdist_egg bdist_wininst
rmdir /s /q build include

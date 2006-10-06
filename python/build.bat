rmdir /s /q build include
mkdir include & xcopy ..\include include
copy ..\include\LICENSE .
rem swig -O -Iinclude -DSCANNER -c++ -python tst.i
del MANIFEST
python setup.py clean sdist bdist_wininst
rmdir /s /q build include

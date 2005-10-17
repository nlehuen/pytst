rmdir /s /q build include
mkdir include & xcopy ..\include include
swig -Iinclude -c++ -python tst.i
python setup.py clean sdist bdist_egg bdist_wininst
rmdir /s /q build include

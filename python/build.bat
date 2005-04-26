rmdir /s /q build dist include
mkdir include & xcopy ..\include include
swig -Iinclude -c++ -python tst.i
python setup.py clean install sdist bdist_wininst
rmdir /s /q build include

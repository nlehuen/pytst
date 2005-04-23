rmdir /s /q build dist
swig -I.. -Iinclude -c++ -python tst.i
python setup.py clean install sdist bdist_wininst

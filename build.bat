rmdir /s /q build dist
swig -c++ -python tst.i
python setup.py clean install sdist bdist_wininst

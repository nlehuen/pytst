rmdir /s /q build
swig -O -I../include -DSCANNER -c++ -python tst.i
python setup.py clean sdist bdist_wininst
rmdir /s /q build

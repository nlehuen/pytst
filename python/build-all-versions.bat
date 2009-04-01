swig -O -I../include -DSCANNER -c++ -python tst.i
for %%p in (23 24 25 26) do (
    c:\python%%p\python.exe setup.py clean build --compile=mingw32 sdist bdist_wininst
    rmdir /s /q build
)

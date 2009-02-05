rmdir /s /q build include
mkdir include & xcopy ..\include include
copy ..\include\LICENSE .
swig -O -Iinclude -DSCANNER -c++ -python tst.i
del MANIFEST
for %%p in (23 24 25 26) do (
    c:\python%%p\python.exe setup.py clean build --compile=mingw32 sdist bdist_wininst
    rmdir /s /q build
)
rmdir /s /q include

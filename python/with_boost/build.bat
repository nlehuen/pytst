bjam -sPYTHON_VERSION=2.4 -sZLIB_SOURCE=d:\projets\zlib-1.2.3 -sPYTHON_ROOT=c:\python24 -sBUILD=release %*
copy bin\boost\libs\python\build\boost_python.dll\vc-7_1\release\threading-multi\boost_python.dll .
copy bin\with_boost\tst.pyd\vc-7_1\release\threading-multi\tst.pyd .
python zipit.py

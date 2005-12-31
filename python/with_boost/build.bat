bjam -sSTLPORT_VERSION_PATH=C:/projets/STLport/stlport -sPYTHON_VERSION=2.4 -sPYTHON_ROOT=e:\python24 -sBUILD=release %*
copy bin\boost\libs\python\build\boost_python.dll\vc-7_1\release\threading-multi\boost_python.dll .
copy bin\with_boost\tst.pyd\vc-7_1\release\threading-multi\tst.pyd .
python zipit.py

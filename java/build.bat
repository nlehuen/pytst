@echo off

rem Compilation de la lib
rmdir /s /q classes
mkdir classes
javac -d classes com\lehuen\tst\*.java

rem Creation du JAR
cd classes
jar cvf ..\com.lehuen.tst.jar com
cd ..

rem Compilation des exemples
javac -classpath com.lehuen.tst.jar *.java

rem Generation de la doc
rmdir /s /q docs
javadoc -d docs com\lehuen\tst\*.java
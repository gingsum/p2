javac Sample1.java
javah Sample1
cl -Ic:\jdk\include -Ic:\jdk\include\win32 -LD Sample1.c -FeSample1.dll
java Sample1
javac test.java
javah test
cl -Ic:\jdk\include -Ic:\jdk\include\win32 -LD test.cpp -Fetest.dll
java test
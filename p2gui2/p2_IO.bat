javac p2_IO.java
javah p2_IO
cl -Ic:\jdk\include -Ic:\jdk\include\win32 -LD p2_IO.cpp -Fep2_IO.dll
java p2_IO
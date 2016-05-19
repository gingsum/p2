javac p2gui.java
javah p2gui
cl -Ic:\jdk\include -Ic:\jdk\include\win32 -LD p2_IO.cpp -Fep2_IO.dll
java p2gui
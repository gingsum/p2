javac p2_GUI.java
javah p2_GUI
cl -Ic:\jdk\include -Ic:\jdk\include\win32 -LD p2_IO.cpp -Fep2_IO.dll
java p2_GUI
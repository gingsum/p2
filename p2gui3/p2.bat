del p2_IO.dll
del p2_IO.exp
del *.log
javac p2gui.java
javah p2gui
cl -I"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include" -Ic:\jdk\include -Ic:\jdk\include\win32 -LD p2_IO.cpp -Fep2_IO.dll
java p2gui

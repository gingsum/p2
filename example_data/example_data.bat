javac example_data.java
javah example_data
cl -Ic:\jdk\include -Ic:\jdk\include\win32 -LD example_data.cpp -Feexample_data.dll
java example_data
javac daysofweek.java
javah daysofweek
cl -Ic:\jdk\include -Ic:\jdk\include\win32 -LD daysofweek
java daysofweek.c -Fedaysofweek.dll
#include "test.h"
#include <string.h>

JNIEXPORT jint JNICALL Java_test_intMethod
  (JNIEnv *env, jobject obj, jint num) {
   return num * num;
}
 
void main(){}
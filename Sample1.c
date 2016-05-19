#include "Sample1.h"
#include <string.h>

int global_int = 0;

JNIEXPORT jint JNICALL Java_Sample1_intMethod
  (JNIEnv *env, jobject obj, jint num) {
    global_int = 10;
   return num * num;
}

JNIEXPORT jboolean JNICALL Java_Sample1_booleanMethod
  (JNIEnv *env, jobject obj, jboolean boolean) {
  return !boolean;
}
JNIEXPORT jstring JNICALL Java_Sample1_stringMethod
  (JNIEnv *env, jobject obj, jstring string) {
    const char *str = (*env)->GetStringUTFChars(env, string, 0);
    char cap[128];
    strcpy(cap, str);
    (*env)->ReleaseStringUTFChars(env, string, str);
    return (*env)->NewStringUTF(env, strupr(cap));
}

JNIEXPORT jint JNICALL Java_Sample1_intArrayMethod
  (JNIEnv *env, jobject obj, jintArray array) {
    int i, sum = 0;
    jsize len = (*env)->GetArrayLength(env, array);
    jint *body = (*env)->GetIntArrayElements(env, array, 0);
    for (i=0; i<len; i++)
    {	sum += body[i];
    }
    (*env)->ReleaseIntArrayElements(env, array, body, 0);
    return sum;
}

JNIEXPORT jintArray JNICALL Java_Sample1_intArray(JNIEnv *env, jobject obj)
{
 jintArray result;
 result = (*env)->NewIntArray(env, 1024);
 if (result == NULL) {
     return NULL; 
 }
 int i;


 jint fill[1024];
 for (i = 0; i < 1024; i++) {
     fill[i] = 0; 
 }
 fill[0] = global_int;
 fill[1] = 1;

 (*env)->SetIntArrayRegion(env, result, 0, 1024, fill);
 return result;
}

 
void main(){}
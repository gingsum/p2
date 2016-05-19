#include "example_data.h"
#include <string.h>

  JNIEXPORT jobjectArray JNICALL   
               Java_example_data  
  (JNIEnv *env, jobject jobj){  

    jobjectArray ret;  
    int i;  

    char *message[5]= {"first",   
                       "second",   
                       "third",   
                       "fourth",   
                       "fifth"};  

    ret= (jobjectArray)env->NewObjectArray(5,  
         env->FindClass("java/lang/String"),  
         env->NewStringUTF(""));  

    for(i=0;i<5;i++) {  
        env->SetObjectArrayElement(  
        ret,i,env->NewStringUTF(message[i]));  
    }  
    return(ret);  
  } 
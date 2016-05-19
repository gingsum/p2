#include "p2_GUI.h"
#include <string.h>

JNIEXPORT jobjectArray JNICALL Java_p2_1gui_name
  (JNIEnv *env, jobject obj){
 	jobjectArray ret;
 	int i;
 	char *name[1024];

 	// input data
 	name[0] = "one";
 	name[1] = "two";

 	ret = (jobjectArray)env->NewObjectArray(5,
 			env->FindClass("java/lang/String"),
 			env->NewStringUTF(" "));
 	for(i = 0; i<1024;i++){
 		env->SetObjectArrayElement(
 			ret,i,env->NewStringUTF(name[i]));
 	}
 	return ret;
}
/*
JNIEXPORT jintArray JNICALL Java_p2_1gui_date
  (JNIEnv *env, jobject obj){
  	jintArray ret;
  	ret = env->NewIntArray(env, 1024);
  	if(ret == NULL){
  		return NULL;
  	}
  	int i;
  	jint date[1024];
  	for(i = 0; i < 1024; i++){
  		date[i] = 0;
  	}

  	//input data
  	date[0] = 123;
  	date[1] = 321;

  	env->SetIntArrayRegion(env,ret,0,1024,date);
  	return ret;
}

JNIEXPORT jbooleanArray JNICALL Java_p2_1gui_type
  (JNIEnv *env, jobject obj){
  	jbooleanArray ret;
  	ret = env->NewBooleanArray(env, 1024);
  	if(ret == NULL){
  		return NULL;
  	}
  	int i;
  	jboolean type[1024];
  	for(i = 0; i < 1024; i++){
  		type[i] = false;
  	}

  	// input data
  	type[0] = true;

  	env->SetBooleanArrayRegion(env,ret,0,1024,type);
  	return ret;
}

JNIEXPORT jlongArray JNICALL Java_p2_1gui_size
  (JNIEnv *env, jobject obj){
  	jlongArray ret;
  	ret = env->NewLongArray(env, 1024);
  	if(ret == NULL){
  		return NULL;
  	}
  	int i;
  	jlong size[1024];
  	for(i = 0; i < 1024; i++){
  		size[i] = 0;
  	}

  	//input data
  	size[0] = 1234152345;
  	size[1] = 8091560921350869;

  	env->SetLongArrayRegion(env,ret,0,1024,size);
  	return ret;
}*/
#include "p2gui.h"
#include <string.h>

//shell.cpp includes
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

#include <stdlib.h>
#include <iostream>

const int MAX_SIZE = 1024;
void DisplayErrorBox(LPTSTR lpszFunction);

struct Dir_Table{
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    long size = 0;
    char filename[64];
    bool folder = false;
} curr_table[MAX_SIZE];    // currently supports MAX_SIZE items in a folder

void print_directory(){
    int index = 0;
    while(curr_table[index].year != 0){
      if(curr_table[index].hour > 12)
        printf("%d/%d/%d  %hd:%d PM", curr_table[index].month, curr_table[index].day, 
              curr_table[index].year, curr_table[index].hour - 12, curr_table[index].minute);
      else
        printf("%d/%d/%d  %hd:%d AM", curr_table[index].month, curr_table[index].day, 
              curr_table[index].year, curr_table[index].hour, curr_table[index].minute);
      if(curr_table[index].folder)
        printf("\t<DIR>\t\t\t%s\n", curr_table[index].filename);
      else
        printf("\t%16ld bytes\t%s\n", curr_table[index].size, curr_table[index].filename);
	  index++;
    }
}

void swap(int index_small, int index_big){
  struct Dir_Table temp = curr_table[index_small];
  curr_table[index_small] = curr_table[index_big];
  curr_table[index_big] = temp;
}

long time_to_seconds(struct Dir_Table element){
  return element.day*86400 + element.hour*3600 + 
         element.minute*60 + element.second;
}

void DisplayErrorBox(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and clean up

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

// DLL STARTS HERE
JNIEXPORT void JNICALL Java_p2gui_resetData
  (JNIEnv *env, jobject obj){
  	int i = 0;
  	for(int i = 0; i < MAX_SIZE; i++){
  		curr_table[i].year = 0;
  		curr_table[i].month = 0;
  		curr_table[i].day = 0;
  		curr_table[i].hour = 0;
  		curr_table[i].minute = 0;
  		curr_table[i].second = 0;
  		curr_table[i].size = 0;
  		curr_table[i].filename[0] = '\0';
  		curr_table[i].folder = false;
  	}
}

int cmpfunc (const void * a, const void * b)
{
  Dir_Table *tableA = (Dir_Table *)a;
  Dir_Table *tableB = (Dir_Table *)b;

  //return strcmp(tableA->filename, tableB->filename);
  return tableA->size - tableB->size;
}

JNIEXPORT jint JNICALL Java_p2gui_setCurrDir
  (JNIEnv *env, jobject obj, jstring currDir){

	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	ULARGE_INTEGER fTime;
	char szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError=0;
	SYSTEMTIME stUTC, st;

 	const char *cd = env->GetStringUTFChars(currDir, 0);

	strcpy(szDir, cd);
    strcat(szDir, "\\*");
	
	// Find the first file in the directory.
	hFind = FindFirstFile(szDir, &ffd);

	if (hFind == INVALID_HANDLE_VALUE)
		DisplayErrorBox(TEXT("FindFirstFile"));

	// List all the files in the directory with some info about them.
	char* timestamp = (char*)malloc(32);
	char* buffer = (char*)malloc(8);
	int index = 0;

	do {
		filesize.LowPart = ffd.nFileSizeLow;
		filesize.HighPart = ffd.nFileSizeHigh;

		// get file last write time
		FileTimeToSystemTime(&ffd.ftLastWriteTime, &stUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &st);

		sprintf(buffer, "%d",st.wYear);
		int year = atoi(buffer);
		sprintf(buffer, "%d",st.wMonth);
		int month = atoi(buffer);
		sprintf(buffer, "%d",st.wDay);
		int day = atoi(buffer);
		sprintf(buffer, "%d",st.wHour);
		int hour = atoi(buffer);
		sprintf(buffer, "%d",st.wMinute);
		int minute = atoi(buffer);
		sprintf(buffer, "%d",st.wSecond);
		int second = atoi(buffer);
		sprintf(buffer, "%d",st.wSecond);
		char* fs = (char*)malloc(32);
		sprintf(fs, "%lld", filesize.QuadPart);

		if (hour > 12)
		  sprintf(timestamp, "%d/%d/%d  %hd:%d PM",
		          st.wMonth, st.wDay, st.wYear, hour - 12, st.wMinute);
		else
		  sprintf(timestamp, "%d/%d/%d  %d:%d AM",
		          st.wMonth, st.wDay, st.wYear, hour, st.wMinute);

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		  // set directory
		  curr_table[index].year = year;
		  curr_table[index].month = month;
		  curr_table[index].day = day;
		  curr_table[index].hour = hour;
		  curr_table[index].minute = minute;
		  curr_table[index].second = second;
		  curr_table[index].folder = true;
		  sprintf(curr_table[index].filename, "%s", ffd.cFileName);
		 // printf("%s\t<DIR>\t\t\t%s\n", timestamp, ffd.cFileName);
		  index++;
		}
		else
		{
		  if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))  /* don't print hidden files */
		  {
		    // set file
		    curr_table[index].year = year;
		    curr_table[index].month = month;
		    curr_table[index].day = day;
		    curr_table[index].hour = hour;
		    curr_table[index].minute = minute;
		    curr_table[index].second = second;
		    curr_table[index].size = atol(fs);
		    curr_table[index].folder = false;
		    sprintf(curr_table[index].filename, "%s", ffd.cFileName);
		 //   printf("%s\t%16s bytes\t%s\n", timestamp, fs, ffd.cFileName);
		    index++;
		  }
		}
	}while (FindNextFile(hFind, &ffd) != 0);
	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES) 
		DisplayErrorBox(TEXT("FindFirstFile"));
	FindClose(hFind);

	env->ReleaseStringUTFChars(currDir, cd);
//	qsort(curr_table, MAX_SIZE, sizeof(Dir_Table), cmpfunc);
	return index;
}

JNIEXPORT jintArray JNICALL Java_p2gui_date
  (JNIEnv *env, jobject obj, jint index){
  	jintArray ret;
  	ret = env->NewIntArray(6);
  	
  	jint date[6];

  	//input data
  	date[0] = curr_table[index].year;
  	date[1] = curr_table[index].month;
  	date[2] = curr_table[index].day;
  	date[3] = curr_table[index].hour;
  	date[4] = curr_table[index].minute;
  	date[5] = curr_table[index].second;

  	env->SetIntArrayRegion(ret,0,6,date);
  	return ret;
}

JNIEXPORT jlong JNICALL Java_p2gui_size
  (JNIEnv *env, jobject obj, jint index){
  	jlong ret;
  	
  	long size = curr_table[index].size;
  	ret = (jlong)size;
  	return ret;
}

JNIEXPORT jstring JNICALL Java_p2gui_name
  (JNIEnv *env, jobject obj, jint index) { 
    jstring ret;

    // input data
    char* name = curr_table[index].filename;
    ret = env->NewStringUTF(name);
    
    return ret;
}

JNIEXPORT jboolean JNICALL Java_p2gui_type
	(JNIEnv *env, jobject obj, jint index) {
	jboolean ret;

	bool type = curr_table[index].folder;
	ret = (jboolean) type;

	return ret;
}

void main(){}
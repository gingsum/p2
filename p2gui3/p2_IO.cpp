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

void DisplayErrorBox(LPTSTR lpszFunction);

struct Dir_Table{
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    long size = 0;
    char* filename = (char*)malloc(64);
    bool folder = false;
} curr_table[1024];    // currently supports 1024 items in a folder

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

void sort_by_size_dec(){	
  int index = 0;
  while (curr_table[index].year != 0){
    int j = index;
    while(curr_table[j].year != 0){
      if(curr_table[index].size < curr_table[j].size){
      	swap(index,j);
      }
      j++;
    }
    index++;
  }   
}
void sort_by_size_asc(){
  int index = 0;
  while (curr_table[index].year != 0){
    int j = index;
    while(curr_table[j].year != 0){
      if(curr_table[index].size > curr_table[j].size)
        swap(index,j);
      j++;
    }
    index++;
  }   
}
void sort_by_time_des(){
  int index = 0;
  while (curr_table[index].year != 0){
    // find the latest time first
    int j = index;
    while(curr_table[j].year != 0){
      if(curr_table[index].year < curr_table[j].year)
        swap(index,j);
      else if(curr_table[index].year == curr_table[j].year)
        if(curr_table[index].month < curr_table[j].month)
          swap(index,j);
        else if(curr_table[index].month == curr_table[j].month)
          if(time_to_seconds(curr_table[index]) < time_to_seconds(curr_table[j]))
              swap(index, j);
      j++;
    }
    index++;
  }
}
void sort_by_time_asc(){
  int index = 0;
  while (curr_table[index].year != 0){
    // find the latest time first
    int j = index;
    while(curr_table[j].year != 0){
      if(curr_table[index].year > curr_table[j].year)
        swap(index,j);
      else if(curr_table[index].year == curr_table[j].year)
        if(curr_table[index].month > curr_table[j].month)
          swap(index,j);
        else if(curr_table[index].month == curr_table[j].month)
          if(time_to_seconds(curr_table[index]) > time_to_seconds(curr_table[j]))
              swap(index, j);
      j++;
    }
    index++;
  }
}
void sort_by_type_dir(){
	int index = 0;
	while (curr_table[index].year != 0){
		if(curr_table[index].folder == true){
			index++;
			continue;
		}
		else {
			int j = index;
			while(curr_table[j].year != 0){
				if(curr_table[j].folder == true){
					swap(index,j);
					break;
				}
				j++;
			}
		}
		index++;
	}
}
void sort_by_type_file(){
	int index = 0;
	while (curr_table[index].year != 0){
		if(curr_table[index].folder == false){
			index++;
			continue;
		}
		else {
			int j = index;
			while(curr_table[j].year != 0){
				if(curr_table[j].folder == false){
					swap(index,j);
					break;
				}
				j++;
			}
		}
		index++;
	}
}
void sort_by_name_dec(){
  int index = 0;
  while (curr_table[index].year != 0){
    int j = index;
    char temp_index[sizeof(curr_table[index].filename)];
    int m;
    for(m = 0; curr_table[index].filename[m]; m++)
    	temp_index[m] = tolower(curr_table[index].filename[m]);
    while(curr_table[j].year != 0){
    	char temp_j[sizeof(curr_table[j].filename)];
    	int n;
    	for(n = 0; curr_table[j].filename[n]; n++)
  		  	temp_index[n] = tolower(curr_table[j].filename[n]);
      	if(strcmp(temp_index,temp_j) > 0)
        	swap(index,j);
      	j++;
    }
    index++;
  }  
}
void sort_by_name_asc(){
  int index = 0;
  while (curr_table[index].year != 0){
    int j = index;
    char temp_index[sizeof(curr_table[index].filename)];
    int m;
    for(m = 0; curr_table[index].filename[m]; m++)
    	temp_index[m] = tolower(curr_table[index].filename[m]);
    while(curr_table[j].year != 0){
    	char temp_j[sizeof(curr_table[j].filename)];
    	int n;
    	for(n = 0; curr_table[j].filename[n]; n++)
  		  	temp_index[n] = tolower(curr_table[j].filename[n]);
      	if(strcmp(temp_index,temp_j) < 0)
        	swap(index,j);
      	j++;
    }
    index++;
  } 
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
  	for(int i = 0; i < 1024; i++){
  		curr_table[i].year = 0;
  		curr_table[i].month = 0;
  		curr_table[i].day = 0;
  		curr_table[i].hour = 0;
  		curr_table[i].minute = 0;
  		curr_table[i].second = 0;
  		curr_table[i].size = 0;
  		curr_table[i].filename = "";
  		curr_table[i].folder = false;
  	}
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
	do
	{
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
	sort_by_name_dec();
//	free(timestamp);
//	free(buffer);
	return index;
}

JNIEXPORT void JNICALL Java_p2gui_goUpOneDir
  (JNIEnv *env, jobject obj){

}

JNIEXPORT void JNICALL Java_p2gui_goToDir
  (JNIEnv *env, jobject obj, jstring dir){

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

JNIEXPORT void JNICALL Java_p2gui_sort
	(JNIEnv *env, jobject obj, jint index){
		sort_by_size_dec();
/*
	if(index == 0){
		char temp1[sizeof(curr_table[0].filename)];
    	int n;
    	for(n = 0; curr_table[0].filename[n]; n++)
  		  	temp1[n] = tolower(curr_table[0].filename[n]);
  		char temp2[sizeof(curr_table[1].filename)];
    	int m;
    	for(m = 0; curr_table[1].filename[m]; m++)
  		  	temp2[m] = tolower(curr_table[1].filename[m]);
      	if(strcmp(temp1,temp2) > 0)
      		sort_by_name_asc();
      	else	
			sort_by_name_dec();
	

		sort_by_name_dec();
	} else if (index == 1){

		sort_by_time_asc();
//		sort_by_time_des();
	} else if (index == 2){
		sort_by_type_file();
//		sort_by_type_dir();
	} else if (index == 3){
		sort_by_size_asc();
//		sort_by_name_dec();
	}*/
}

void main(){}
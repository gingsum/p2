#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <string.h>
#pragma comment(lib, "User32.lib")

#include <stdlib.h>

void DisplayErrorBox(LPTSTR lpszFunction);

struct Dir_Table{
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    long long size = 0;
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
        printf("\t%16lld bytes\t%s\n", curr_table[index].size, curr_table[index].filename);
index++;
    }
}

void swap(int index_small, int index_big){
  struct Dir_Table temp = curr_table[index_small];
  curr_table[index_small] = curr_table[index_big];
  curr_table[index_big] = temp;
}

long long time_to_seconds(struct Dir_Table element){
  return element.day*86400 + element.hour*3600 + 
         element.minute*60 + element.second;
}

void sort_by_size(){
  int index = 0;
  while (curr_table[index].year != 0){
      // find the   int index = 0;
      //largest file first 
    int j = index;
    while(curr_table[j].year != 0){
      if(curr_table[index].size < curr_table[j].size)
        swap(index,j);
      j++;
    }
    index++;
  }   
}

void sort_by_time(){
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

int main(int argc, TCHAR *argv[])
{
   WIN32_FIND_DATA ffd;
   LARGE_INTEGER filesize;
   ULARGE_INTEGER fTime;
   char szDir[MAX_PATH];
   HANDLE hFind = INVALID_HANDLE_VALUE;
   DWORD dwError=0;
   SYSTEMTIME stUTC, st;
   
   // If the directory is not specified as a command-line argument,
   // print usage.

   if (!((argc == 4) || (argc == 5)))
   {
      printf("# of argc = %d\n",argc);
      printf("\nUsage: %s <command and options>\n", argv[0]);
      printf("Command 1: dir <path> <option>\n");
      printf("Command 2: compare <file1> <file2> [optional masking character]\n");
      return (-1);
   }

   if (stricmp(argv[1], "dir") == 0)
   {
     // Check that the input path plus options is not longer than MAX_PATH.
     // Three characters are for the "\*" plus NULL appended below.

     if (strlen(argv[2]) > (MAX_PATH - 3))
     {
        printf("\nDirectory path is too long.\n");
        return (-1);
     }

     printf("\nDirectory of %s\n\n", argv[2]);

     // Prepare string for use with FindFile functions.  First, copy the
     // string to a buffer, then append '\*' to the directory name.

     strcpy(szDir, argv[2]);
     strcat(szDir, "\\*");

     // Find the first file in the directory.

     hFind = FindFirstFile(szDir, &ffd);
  
     if (hFind == INVALID_HANDLE_VALUE)
     {
       DisplayErrorBox(TEXT("FindFirstFile"));
       return dwError;
     } 
   
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
            curr_table[index].size = atoll(fs);
            curr_table[index].folder = false;
            sprintf(curr_table[index].filename, "%s", ffd.cFileName);
         //   printf("%s\t%16s bytes\t%s\n", timestamp, fs, ffd.cFileName);
            index++;
          }
        }
     }
     while (FindNextFile(hFind, &ffd) != 0);

     int i, j;
     if(stricmp(argv[3], "/zd") == 0){
      // sort by time, latest first
        sort_by_time();
        print_directory();
     } else if (stricmp(argv[3], "/zs") == 0){
      // sort by size, largest first
        sort_by_size();
        print_directory();
     }
 
     dwError = GetLastError();
     if (dwError != ERROR_NO_MORE_FILES) 
     {
       DisplayErrorBox(TEXT("FindFirstFile"));
     }

     FindClose(hFind);
     return dwError;
  } else if (stricmp(argv[1], "compare") == 0){
    // start "compare" command here
    FILE *file1;
    FILE *file2;
    file1 = fopen(argv[2], "r");
    file2 = fopen(argv[3], "r");
    int f1;
    int f2;
    char* arg_4 = (char*) malloc(1);
    char* s_f1  = (char*) malloc(1);
    char* s_f2  = (char*) malloc(1);

    sprintf(arg_4,"%s",argv[4]);
    int char_index = 1;    
    while ((f1 = fgetc(file1)) != EOF ){
      f2 = fgetc(file2);
      sprintf(s_f1,"%c",f1);
      sprintf(s_f2,"%c",f2);

//      printf("%d %d %s %s %s\n",stricmp(arg_4, s_f1),stricmp(arg_4,s_f2),arg_4,s_f1,s_f2 );
      if (argv[4] == NULL){
        if (f1 != f2){
            printf("Character at index %d failed comparison: %c != %c\n", char_index, f1, f2);
            break;
          }
      } else if(stricmp(arg_4, s_f1) != 0 && stricmp(arg_4,s_f2) != 0){
       // printf ("%d %d %d\n",(int)argv[4],f1,f2 );
          if (f1 != f2){
            printf("Character at index %d failed comparison: %c != %c\n", char_index, f1, f2);
            break;
          }
      }
      char_index++;
    }
    if (f1 == EOF)
      printf("%s and %s contain the same code\n", argv[2], argv[3]);

    free(arg_4);
    free(s_f1);
    free(s_f2);
    fclose(file1);
    fclose(file2); 
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

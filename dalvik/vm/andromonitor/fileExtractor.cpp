#include "fileExtractor.h"

int 
fileExtractor(const char* filename)
{
    char copyFilePath[512] = "/data/andromonitor/";
    char str_temp[512] = {0,};
    char str_fileIndex[3] = {0,};

    int fd1 = -1;
    int fd2 = -1;

    struct stat buf;
    size_t size;
    
    snprintf(str_fileIndex, 2, "%d", gAndromonitor.fileIndex);
    gAndromonitor.fileIndex += 1;

    strcpy(str_temp, str_fileIndex);
    strcat(str_temp, filename);

    for(int i = strlen(str_fileIndex); str_temp[i] != 0 ; i++){
        if(str_temp[i] == '/')
            str_temp[i] = '_';
    }
    
    strcat(copyFilePath, str_temp);

    ALOGE("MSEC|fileExtractor filename = %s, copyFilePath = %s ", filename, copyFilePath);
    fd1 = open(filename, O_RDONLY, 0);
    ALOGE("MSEC|fileExtractor fd1 = %d",fd1);
    fd2 = open(copyFilePath, O_CREAT|O_RDWR, 0644);
    ALOGE("MSEC|fileExtractor fd2 = %d",fd2);
    fstat(fd1, &buf);
    size = (size_t) buf.st_size;
    ALOGE("MSEC|fileExtractor (size_t) buf.st_size = %d",size);
    sysCopyFileToFile(fd2,fd1,size);

    close(fd1);
    close(fd2);
    return 1;
}


// int
// getFileName(const char* fullPath,char* ptr) {
//     char str[256] = {0,};
//     strncpy(str,fullPath,sizeof(fullPath));

//     ptr=strtok(str,"/");
//     while( (ptr=strtok(NULL,"/")) != NULL )
//     {

//     }
//     return 1;
// }



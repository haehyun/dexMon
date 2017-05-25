#include "myprintf.h"

int myPrintf(const char* fmt, ...)
{
    int i;
    int fd;
    char buf[4000] = {0};

	umask(000);
    if(gInterpPortable.currentPackageMode == PRINT_MODE){
        fd = open("/data/andromonitor/msec.code", 00000001 | 00002000 | 00000100, 0666);
    } else if(gInterpPortable.currentPackageMode == MONITOR_MODE){
        fd = open("/data/andromonitor/msec.log", 00000001 | 00002000 | 00000100, 0666);
    } else if(gInterpPortable.currentPackageMode == SANITIZE_SERVER_CORECODE_MODE) {
        fd = open("/data/andromonitor/msec.hash", 00000001 | 00002000 | 00000100, 0666);
    } else {
        fd = -1;
    }
    //int fd = open(path, 00000001 | 00002000 | 00000100, 0666);

    if(fd == -1){
        ALOGE("msec|myPrintf fail");
        myClose(0, NULL);
    }

    va_list args;
  
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end (args);
 
    if(gInterpPortable.currentPackageMode == PRINT_MODE){
        
    }
    else {
        i = strlen(buf);
        if(i == 4000)
            i = 3998;
        buf[i] = '\n';
        buf[i+1] = '\0';
    }

    write(fd, buf, strlen(buf));

    close(fd);
    return 1;
}

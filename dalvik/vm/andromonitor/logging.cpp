#include "logging.h"

int logging(const char* fmt, ...)
{
    //ALOGE("HaehyunDEBUG logging Function start\n");
    int fd = 0;
    int i = 0;
    char buf[8192] = {0,};

	umask(000);
    fd = open("/data/andromonitor/log.txt", 00000001 | 00002000 | 00000100, 0666);
  
    if(fd == -1){
        ALOGE("Error log.txt can't open");
        dvmAbort();
    }

    va_list args;
  
    va_start(args, fmt);
    vsnprintf(buf, 8191, fmt, args);
    va_end (args);
 
    i = strlen(buf);
    if(i == 8191)
        i = 8190;
    buf[i] = '\n';
    buf[i+1] = '\0';

    //ALOGE("HaehyunDEBUG write Function start\n");
    //write(fd, buf, strlen(buf));
    
    write(fd, buf, strlen(buf));
    

    close(fd);
    return 1;
}

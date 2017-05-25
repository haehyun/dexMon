#ifndef DALVIK_ANDROMONITOR_FILEEXTRACTOR_MODULE
#define DALVIK_ANDROMONITOR_FILEEXTRACTOR_MODULE

#include "Dalvik.h"
#include "libdex/OptInvocation.h"
#include "cutils/log.h"
#include "cutils/process_name.h"

#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

int fileExtractor(const char* filename);
// int getFileName(const char* fullPath,char* ptr);

#endif  //DALVIK_ANDROMONITOR_FILEEXTRACTOR_MODULE
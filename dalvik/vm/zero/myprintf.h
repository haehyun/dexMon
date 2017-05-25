#ifndef DALVIK_MYPRINT_MODULE
#define DALVIK_MYPRINT_MODULE

#include "Dalvik.h"
#include "cutils/log.h"
#include "cutils/process_name.h"

#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

int myPrintf(const char* fmt, ...);

#endif  // DALVIK_MYPRINT_MODULE
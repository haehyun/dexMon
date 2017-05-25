#ifndef DALVIK_SETAPP_MODULE
#define DALVIK_SETAPP_MODULE

#include "Dalvik.h"
#include "cutils/log.h"
#include "cutils/process_name.h"

#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
void readAppList();
int setCurrentPackageMode();
char* setCurrentPackageName();
int setCurrentPackageModeAndName();


#endif  // DALVIK_OPENSSL_MODULE
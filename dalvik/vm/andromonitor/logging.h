#ifndef DALVIK_ANDROMONITOR_LOGGING_MODULE
#define DALVIK_ANDROMONITOR_LOGGING_MODULE

#include "Dalvik.h"
#include "cutils/log.h"
#include "cutils/process_name.h"

#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

int logging(const char* fmt, ...);

#endif  // DALVIK_ANDROMONITOR_LOGGING_MODULE
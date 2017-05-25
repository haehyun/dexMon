#ifndef DALVIK_MYCLOSE_MODULE
#define DALVIK_MYCLOSE_MODULE

#include "Dalvik.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <signal.h>

int myClose(int flag, Thread* self);

#endif  // DALVIK_MYCLOSE_MODULE
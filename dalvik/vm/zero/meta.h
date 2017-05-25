#ifndef DALVIK_META_MODULE
#define DALVIK_META_MODULE

#include "Dalvik.h"
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

void signCheck(const char* pname);
void hashCheck(const char* pname);

#endif  // DALVIK_META_MODULE
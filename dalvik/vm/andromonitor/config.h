#ifndef DALVIK_ANDROMONITOR_CONFIG_MODULE
#define DALVIK_ANDROMONITOR_CONFIG_MODULE

#include "Dalvik.h"
#include "cutils/log.h"
#include "cutils/process_name.h"

#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

int andromonitorConfig(void);
int getVariableNumber(char *line,int size);
int setVariable(int n, char *line, int size);
int getCurrentPackageName(void);

#endif  //DALVIK_ANDROMONITOR_CONFIG_MODULE
#ifndef DALVIK_ANDROMONITOR_DEOBFCONVERTER_MODULE
#define DALVIK_ANDROMONITOR_DEOBFCONVERTER_MODULE

#include "Dalvik.h"

void deobfConvertUtf16ToUtf8(char* utf8Str, const u2* utf16Str, int len);

#endif  //DALVIK_ANDROMONITOR_DEOBFCONVERTER_MODULE
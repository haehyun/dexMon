#ifndef DALVIK_BASE64_MODULE_
#define DALVIK_BASE64_MODULE_

#include "Dalvik.h"
#include <stdlib.h>
#include <ctype.h>

const char Base64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char Pad64 = '=';
int base64_encode(char *src, size_t srclength, char *target, size_t targsize);
int base64_decode(char const *src, u_char *target, size_t targsize);

#endif  // DALVIK_BASE64_MODULE_
#ifndef DALVIK_ANDROMONITOR_DEOBFPARAM_MODULE
#define DALVIK_ANDROMONITOR_DEOBFPARAM_MODULE

#include "Dalvik.h"

# define DEOBFLOG(...)  do {                                                                          \
        if( (self->threadId == gAndromonitor.threadNumber || gAndromonitor.threadNumber == 0) ){      \
                char debugStrBuf[4098];                                                               \
                snprintf(debugStrBuf, sizeof(debugStrBuf), __VA_ARGS__);                              \
                if (curMethod != NULL){                                                               \
                    logging("|%d|%s", self->threadId, debugStrBuf);                                   \
                }                                                                                     \
                else if(curMethod == NULL)                                                            \
                    logging("|%d|pc=####>%s\n", self->threadId, debugStrBuf);                         \
        }                                                                                             \
    } while(false)


/*
 * This method is handler that to print the parameters.
 * Return value is the last index of paramStrIdx for handled parameter.
 */
char* deobfPrintParam(Thread* self, /*u4* fp, */ const u2* pc, const Method* curMethod, char* paramStrIdx, int paramNum, ArrayObject* arrayObj);

#endif  //DALVIK_ANDROMONITOR_DEOBFPARAM_MODULE
#include "deobfParam.h"

char* deobfPrintParam(Thread* self, /*u4* fp, */ const u2* pc, const Method* curMethod, char* paramStrIdx, int paramNum, ArrayObject* arrayObj) {
    u1*     z = NULL;
    s1*     b = NULL;
    u2*     c = NULL;
    s2*     s = NULL;
    s4*     i = NULL;
    s8*     j = NULL;
    float*  f = NULL;
    double* d = NULL;
    Object* l = NULL;

    char* processedParamStrIdx = paramStrIdx;
    char paramStr[256] = {0};
    char* utf8Str = NULL;
    Object* tmpObj = NULL;


    if(arrayObj == NULL || arrayObj->length == 0){
        switch(*paramStrIdx) {
        case 'Z': case 'B': case 'C': case 'S': case 'I': case 'J': case 'F': case 'D':
            DEOBFLOG("param%d %c[] (NULL)", paramNum, *paramStrIdx);
        case 'L':
            for(int j=0; (paramStr[j] = *paramStrIdx); ++j) {
                paramStrIdx++;
                processedParamStrIdx++;
                if(*paramStrIdx == ';') {
                    paramStr[j+1] = ';';
                    paramStr[j+2] = '\0';
                    break;
                }
            }
            DEOBFLOG("param%d %s[] (NULL)", paramNum, paramStr);
            break;
        case '[':
            processedParamStrIdx = deobfPrintParam(self,/* fp,*/ pc, curMethod, paramStrIdx+1, paramNum, (ArrayObject*)tmpObj);
            break;
        default:
            DEOBFLOG("param%d unknown[] (NULL)", paramNum);
            break;
        }
    } else {
        // DEOBFLOG("[%d]", arrayObj->length);
        switch(*paramStrIdx) {
        case 'Z':
            for(u4 myIdx=0; 8*myIdx < arrayObj->length; ++myIdx) {
                z = (u1*)(void*)&arrayObj->contents[myIdx];
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx, *z);
                if(8*myIdx+1 == arrayObj->length)
                    break;
                z++;
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx+1, *z);
                if(8*myIdx+2 == arrayObj->length)
                    break;
                z++;
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx+2, *z);
                if(8*myIdx+3 == arrayObj->length)
                    break;
                z++;
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx+3, *z);
                if(8*myIdx+4 == arrayObj->length)
                    break;
                z++;
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx+4, *z);
                if(8*myIdx+5 == arrayObj->length)
                    break;
                z++;
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx+5, *z);
                if(8*myIdx+6 == arrayObj->length)
                    break;
                z++;
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx+6, *z);
                if(8*myIdx+7 == arrayObj->length)
                    break;
                z++;
                DEOBFLOG("param%d Z[%d] %u", paramNum, 8*myIdx+7, *z);
            }
            break;
        case 'B':
            for(u4 myIdx=0; 8*myIdx < arrayObj->length; ++myIdx) {
                b = (s1*)(void*)&arrayObj->contents[myIdx];
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx, *b);
                if(8*myIdx+1 == arrayObj->length)
                    break;
                b++;
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx+1, *b);
                if(8*myIdx+2 == arrayObj->length)
                    break;
                b++;
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx+2, *b);
                if(8*myIdx+3 == arrayObj->length)
                    break;
                b++;
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx+3, *b);
                if(8*myIdx+4 == arrayObj->length)
                    break;
                b++;
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx+4, *b);
                if(8*myIdx+5 == arrayObj->length)
                    break;
                b++;
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx+5, *b);
                if(8*myIdx+6 == arrayObj->length)
                    break;
                b++;
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx+6, *b);
                if(8*myIdx+7 == arrayObj->length)
                    break;
                b++;
                DEOBFLOG("param%d B[%d] %d", paramNum, 8*myIdx+7, *b);
            }
            break;
        case 'C':
            utf8Str = (char*)malloc(5);
            for(u4 myIdx=0; 4*myIdx < arrayObj->length; ++myIdx) {
                c = (u2*)(void*)&arrayObj->contents[myIdx];
                deobfConvertUtf16ToUtf8(utf8Str, c, 1); 
                DEOBFLOG("param%d C[%d] %s", paramNum, 4*myIdx, utf8Str);
                if(4*myIdx+1 == arrayObj->length)
                    break;
                c++;
                deobfConvertUtf16ToUtf8(utf8Str, c, 1); 
                DEOBFLOG("param%d C[%d] %s", paramNum, 4*myIdx+1, utf8Str);
                if(4*myIdx+2 == arrayObj->length)
                    break;
                c++;
                deobfConvertUtf16ToUtf8(utf8Str, c, 1); 
                DEOBFLOG("param%d C[%d] %s", paramNum, 4*myIdx+2, utf8Str);
                if(4*myIdx+3 == arrayObj->length)
                    break;
                c++;
                deobfConvertUtf16ToUtf8(utf8Str, c, 1); 
                DEOBFLOG("param%d C[%d] %s", paramNum, 4*myIdx+3, utf8Str);
            }
            free(utf8Str);
            break;
        case 'S':
            for(u4 myIdx=0; 4*myIdx < arrayObj->length; ++myIdx) {
                s = (s2*)(void*)&arrayObj->contents[myIdx]; 
                DEOBFLOG("param%d S[%d] %d", paramNum, 4*myIdx, *s);
                if(4*myIdx+1 == arrayObj->length)
                    break;
                s++; 
                DEOBFLOG("param%d S[%d] %d", paramNum, 4*myIdx+1, *s);
                if(4*myIdx+2 == arrayObj->length)
                    break;
                s++; 
                DEOBFLOG("param%d S[%d] %d", paramNum, 4*myIdx+2, *s);
                if(4*myIdx+3 == arrayObj->length)
                    break;
                s++; 
                DEOBFLOG("param%d S[%d] %d", paramNum, 4*myIdx+3, *s);
            }
            break;
        case 'I':
            for(u4 myIdx=0; 2*myIdx < arrayObj->length; ++myIdx) {
                i = (s4*)(void*)&arrayObj->contents[myIdx]; 
                DEOBFLOG("param%d I[%d] %d", paramNum, 2*myIdx, *i);
                if(2*myIdx+1 == arrayObj->length)
                    break;
                i++; 
                DEOBFLOG("param%d I[%d] %d", paramNum, 2*myIdx+1, *i);
            }
            break;
        case 'J':
            for(u4 myIdx=0; myIdx < arrayObj->length; ++myIdx) {
                j = (s8*)(void*)&arrayObj->contents[myIdx]; 
                DEOBFLOG("param%d J[%d] %lld", paramNum, myIdx, *j);
            }
            break;
        case 'F':
            for(u4 myIdx=0; 2*myIdx < arrayObj->length; ++myIdx) {
                f = (float*)(void*)&arrayObj->contents[myIdx]; 
                DEOBFLOG("param%d F[%d] %f", paramNum, 2*myIdx, *f);
                if(2*myIdx+1 == arrayObj->length)
                    break;
                f++; 
                DEOBFLOG("param%d F[%d] %f", paramNum, 2*myIdx+1, *f);
            }
            break;
        case 'D':
            for(u4 myIdx=0; myIdx < arrayObj->length; ++myIdx) {
                d = (double*)(void*)&arrayObj->contents[myIdx]; 
                DEOBFLOG("param%d D[%d] %lf", paramNum, myIdx, *d);
            }
            break;
        case 'L':
            for(int j=0; (paramStr[j] = *paramStrIdx); ++j) {
                paramStrIdx++;
                processedParamStrIdx++;
                if(*paramStrIdx == ';') {
                    paramStr[j+1] = ';';
                    paramStr[j+2] = '\0';
                    break;
                }
            }

            for(u4 myIdx=0; 2*myIdx < arrayObj->length; ++myIdx) {
                // l = (Object*)(void*)&arrayObj->contents[myIdx]; 
                l = (Object*)(arrayObj->contents[myIdx] & 0x00000000ffffffff);
                if(strncmp(paramStr, "Ljava/lang/String;", strlen("Ljava/lang/String;")) == 0) {
                    DEOBFLOG("param%d %s[%d] %s", paramNum, paramStr, 2*myIdx, dvmCreateCstrFromString((StringObject*)l));
                } else {
                    if(l != NULL) {
                        DEOBFLOG("param%d %s[%d] %p", paramNum, l->clazz->descriptor, 2*myIdx, l);
                    } else {
                        DEOBFLOG("param%d (NULL)[%d] %p", paramNum, 2*myIdx, l);
                    }
                }
                if(2*myIdx+1 == arrayObj->length)
                    break;
                l = (Object*)(arrayObj->contents[myIdx] >> 32);
                if(strncmp(paramStr, "Ljava/lang/String;", strlen("Ljava/lang/String;")) == 0) {
                    DEOBFLOG("param%d %s[%d] %s", paramNum, paramStr, 2*myIdx+1, dvmCreateCstrFromString((StringObject*)l));
                } else {
                    if(l != NULL) {
                        DEOBFLOG("param%d %s[%d] %p", paramNum, l->clazz->descriptor, 2*myIdx+1, l);
                    } else {
                        DEOBFLOG("param%d (NULL)[%d] %p", paramNum, 2*myIdx+1, l);
                    }
                }
            }
            break;
        case '[':
            for(u4 myIdx=0; 2*myIdx < arrayObj->length; ++myIdx) {
                tmpObj = (Object*)(arrayObj->contents[myIdx] & 0x00000000ffffffff);
                processedParamStrIdx = deobfPrintParam(self,/* fp,*/ pc, curMethod, paramStrIdx+1, paramNum, (ArrayObject*)tmpObj);
                if(2*myIdx+1 == arrayObj->length)
                    break;
                tmpObj = (Object*)(arrayObj->contents[myIdx] >> 32);
                processedParamStrIdx = deobfPrintParam(self,/* fp,*/ pc, curMethod, paramStrIdx+1, paramNum, (ArrayObject*)tmpObj);
            }
            break;
        default:
            DEOBFLOG("param%d unknown", paramNum);
            break;
        }
    }
    return processedParamStrIdx;
}

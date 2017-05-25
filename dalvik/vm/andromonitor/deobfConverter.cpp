#include "deobfConverter.h"

/*
 * Convert a UTF-16 string to UTF-8.
 *
 * Make sure you allocate "utf8Str" with the result of utf16_utf8ByteLen(),
 * not just "len".
 */
void deobfConvertUtf16ToUtf8(char* utf8Str, const u2* utf16Str, int len)
{
    while (len--) {
        unsigned int uic = *utf16Str++;

        /*
         * The most common case is (uic > 0 && uic <= 0x7f).
         */
        if (uic == 0 || uic > 0x7f) {
            if (uic > 0x07ff) {
                *utf8Str++ = (uic >> 12) | 0xe0;
                *utf8Str++ = ((uic >> 6) & 0x3f) | 0x80;
                *utf8Str++ = (uic & 0x3f) | 0x80;
            } else /*(uic > 0x7f || uic == 0)*/ {
                *utf8Str++ = (uic >> 6) | 0xc0;
                *utf8Str++ = (uic & 0x3f) | 0x80;
            }
        } else {
            *utf8Str++ = uic;
        }
    }

    *utf8Str = '\0';
}
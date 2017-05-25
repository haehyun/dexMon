#ifndef DALVIK_OPENSSL_MODULE
#define DALVIK_OPENSSL_MODULE

#include "Dalvik.h"
#include <dlfcn.h>
#include <stddef.h>
#include <openssl/aes.h>

// AES Encryption
bool encrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned char* key);
// AES Decryption
bool decrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned char* key);

#endif  // DALVIK_OPENSSL_MODULE
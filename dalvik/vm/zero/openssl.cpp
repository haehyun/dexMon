#include "openssl.h"

bool encrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned char* key)
{
    AES_KEY encKey;
    void *handle = NULL;
    int (*my_AES_set_encrypt_key)(const unsigned char *, const int, AES_KEY *);
    void (*my_AES_encrypt)(const unsigned char *, unsigned char *, const AES_KEY *);
    handle = dlopen("/system/lib/libcrypto.so", RTLD_GLOBAL | RTLD_NOW );
    
    if ( !handle )
    { 
        ALOGE("Good-night Kiss fail to dlopen, %s\n", dlerror());
        return 0;
    }
    
    my_AES_set_encrypt_key = (int (*)(const unsigned char *, const int, AES_KEY *))dlsym(handle, "AES_set_encrypt_key");
    my_AES_encrypt = (void (*)(const unsigned char *, unsigned char *, const AES_KEY *))dlsym(handle, "AES_encrypt");
    /*if ( dlerror() != NULL )
    {
        ALOGE("Good-night Kiss fail to dlsym, %s\n", dlerror());
        return 0;
    }*/
    my_AES_set_encrypt_key(key, 128, &encKey);
    // if (AES_set_encrypt_key(key, 128, &encKey) < 0)
    // {
    //     return false;
    // }
    my_AES_encrypt(plainText, cipherText, &encKey);
    dlclose(handle);
    return true;
}

// AES Decryption
bool decrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned char* key)
{
    AES_KEY decKey;
    void *handle = NULL;
    int (*my_AES_set_decrypt_key)(const unsigned char *, const int, AES_KEY *);
    void (*my_AES_decrypt)(const unsigned char *, unsigned char *, const AES_KEY *);
    handle = dlopen("/system/lib/libcrypto.so", RTLD_GLOBAL | RTLD_LAZY );
    
    if ( !handle )
    { 
        ALOGE("Good-night Kiss fail to dlopen, %s\n", dlerror());
        return 0;
    }
    
    my_AES_set_decrypt_key = (int (*)(const unsigned char *, const int, AES_KEY *))dlsym(handle, "AES_set_decrypt_key");
    my_AES_decrypt = (void (*)(const unsigned char *, unsigned char *, const AES_KEY *))dlsym(handle, "AES_decrypt");
    // if ( dlerror() != NULL )
    // {
    //     ALOGE("Good-night Kiss fail to dlsym, %s\n", dlerror());
    //     return 0;
    // }
    my_AES_set_decrypt_key(key, 128, &decKey);
    // if (AES_set_decrypt_key(key, 128, &decKey) < 0)
    // {
    //     return false;
    // }
    my_AES_decrypt(cipherText, plainText, &decKey);
    dlclose(handle);
    return true;
}
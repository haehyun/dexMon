#include "meta.h"

static int openRSA(const char* zipFileName, const char* rsaName);
static int signcmp(char *src, int srcLen, char *dst, int dstLen);
static int openSHA(const char* zipFileName, const char* shaName);
static int hashcmp(char *src, int srcLen, char *dst, int dstLen);

void signCheck(const char* appName){
    int fd1 = -1,fd2 = -1;
    char appPath[256],rsaName[256],originalRsaName[256];
    char appRsa[2048],originalRsa[2048];
    int result=-1;
    //const char* rsaName = "/data/temp/[appName].RSA";
    
    off_t start, end;
    size_t length,length2;

    sprintf(appPath, "/data/app/%s-1.apk", appName);
    sprintf(rsaName, "/data/temp/%s.RSA", appName); 
    // sprintf(originalRsaName, "/data/temp/%s.RSA.original", appName);
    
    //////////////////////////////////////////////////////////
    /* Dongle ver */
    // sprintf(appPath, "/data/app/%s-1.apk", appName);
    //sprintf(rsaName, "/storage/usbdisk/%s.RSA", appName);
    //sprintf(originalRsaName, "/storage/usbdisk/%s.RSA.original", appName);//CERT.RSA
    sprintf(originalRsaName, "/storage/usbdisk/%s/CERT.RSA", appName);

    if(openRSA(appPath, rsaName) < 0){
        sprintf(appPath, "/data/app/%s-2.apk", appName);
        if(openRSA(appPath, rsaName) < 0){
            ALOGE("%s file zip open failed",appPath);
            myClose(TAMPER_DONGLE_SIGN,NULL);
        }
    }



    fd1 = open(rsaName, O_RDONLY | 0);
    if(fd1 < 0){
        ALOGE("%s OPEN FAILED",rsaName);
        myClose(TAMPER_DONGLE_SIGN,NULL);
    }

    //fgets(appRsa, sizeof(appRsa)-1,fd1);
    start = lseek(fd1, 0L, SEEK_SET);
    read(fd1,appRsa,sizeof(appRsa));
    //ALOGE("name = %s APP RSA = %s",rsaName,appRsa);
    end = lseek(fd1, 0L, SEEK_END);
    (void) lseek(fd1, start, SEEK_SET);
    if (start == (off_t) -1 || end == (off_t) -1) {
        ALOGE("could not determine length of file 1");
        close(fd1);
        unlink(rsaName);
        myClose(TAMPER_DONGLE_SIGN,NULL);
    }
    length = end - start;
    //ALOGE("length = %d",length);


    ALOGE("open path [%s] ",originalRsaName);
    fd2 = open(originalRsaName, O_RDONLY | 0);
    if(fd2 < 0){
        ALOGE("%s open failed",originalRsaName);
        close(fd1);
        unlink(rsaName);
        myClose(TAMPER_DONGLE_SIGN,NULL);
    }
    
    start = lseek(fd2, 0L, SEEK_SET);
    read(fd2,originalRsa,sizeof(originalRsa));
    //ALOGE("name = %s original RSA = %s",originalRsaName,originalRsa);
    end = lseek(fd2, 0L, SEEK_END);
    (void) lseek(fd2, start, SEEK_SET);
    if (start == (off_t) -1 || end == (off_t) -1) {
        ALOGE("could not determine length of file 2");
        close(fd1);
        close(fd2);
        unlink(rsaName);
        myClose(TAMPER_DONGLE_SIGN,NULL);
    }
    length2 = end - start;



    /*
     * comparison code
     */
    result = signcmp(appRsa, (int)length, originalRsa, (int)length2);

    close(fd1);
    close(fd2);
    unlink(rsaName);
    if(result == 0) {
       myClose(TAMPER_DONGLE_SIGN,NULL);
    }    
}

int openRSA(const char* zipFileName, const char* rsaName){
    int result = 0;
    const char* fileToExtract = "META-INF/CERT.RSA";
    ZipArchive archive;
    ZipEntry entry;
    bool unlinkOnFailure = false;
    int fd = -1;

    if (dexZipOpenArchive(zipFileName, &archive) != 0) {
        ALOGE("Unable to open '%s' as zip archive\n",
         zipFileName);
        result = -1;
        goto bail;
    }

    fd = open(rsaName, 00000001 | 00002000 | 00000100, 0666);
    if (fd < 0) {
        ALOGE("Unable to create output file '%s'",rsaName);
        result = -1;
        goto bail;
    }

    unlinkOnFailure = true;

    entry = dexZipFindEntry(&archive, fileToExtract);
    if (entry == NULL) {
        ALOGE("Unable to find '%s' in '%s'\n",
         fileToExtract, zipFileName);
        result = -1;
        goto bail;
    }

    if (dexZipExtractEntryToFile(&archive, entry, fd) != 0) {
        ALOGE("Extract of '%s' from '%s' failed\n",
         fileToExtract, zipFileName);
        result = -1;
        goto bail;
    }

bail:
    if (fd >= 0)
        close(fd);
    if (unlinkOnFailure && result != 0)
        unlink(rsaName);
    dexZipCloseArchive(&archive);
    return result;
}

int signcmp(char *src, int srcLen, char *dst, int dstLen){
    int isSame = 1;
    int i;

    if(srcLen == 0 || dstLen == 0) {
        goto bail;
    } else if(srcLen != dstLen) {
        goto bail;
    } else {
        for(i=0; i<srcLen; i++) {
            if(src[i] != dst[i]) {
                isSame = 0;
                break;
            }
        }
    }

    if(isSame) {
        ALOGE("APPICATION SIGN VALUE IS VERIFYED");
        return 1;  
    } else {
bail:
        ALOGE("APPICATION SIGN VALUE IS DIFFERENT!!");
        return 0;  
    } 
}

///////////////////////////////////////////////////////////////////////////////////////////////
/*
 * hash func
 */

void hashCheck(const char* appName){
    int fd1 = -1,fd2 = -1;
    char appPath[256],shaName[256],originalShaName[256];
    char appSha[2048],originalSha[2048];
    int result=-1;
    //const char* shaName = "/data/temp/[appName].SHA";
    
    off_t start, end;
    size_t length,length2;

    sprintf(appPath, "/data/app/%s-1.apk", appName);
    sprintf(shaName, "/data/temp/%s.SHA", appName); 
    sprintf(originalShaName, "/storage/usbdisk/%s/SHA", appName);

    if(openSHA(appPath, shaName) < 0){
        sprintf(appPath, "/data/app/%s-2.apk", appName);
        if(openSHA(appPath, shaName) < 0){
            ALOGE("%s file zip open failed",appPath);
            myClose(TAMPER_DONGLE_HASH,NULL);
        }
    }



    fd1 = open(shaName, O_RDONLY | 0);
    if(fd1 < 0){
        ALOGE("%s OPEN FAILED",shaName);
        myClose(TAMPER_DONGLE_HASH,NULL);
    }

    //fgets(appSha, sizeof(appSha)-1,fd1);
    start = lseek(fd1, 0L, SEEK_SET);
    read(fd1,appSha,sizeof(appSha));
    //ALOGE("name = %s APP SHA = %s",shaName,appSha);
    end = lseek(fd1, 0L, SEEK_END);
    (void) lseek(fd1, start, SEEK_SET);
    if (start == (off_t) -1 || end == (off_t) -1) {
        ALOGE("could not determine length of file 1");
        close(fd1);
        unlink(shaName);
        myClose(TAMPER_DONGLE_HASH,NULL);
    }
    length = end - start;
    //ALOGE("length = %d",length);



    fd2 = open(originalShaName, O_RDONLY | 0);
    if(fd2 < 0){
        ALOGE("%s open failed",originalShaName);
        close(fd1);
        unlink(shaName);
        myClose(TAMPER_DONGLE_HASH,NULL);
    }
    
    start = lseek(fd2, 0L, SEEK_SET);
    read(fd2,originalSha,sizeof(originalSha));
    //ALOGE("name = %s original SHA = %s",originalShaName,originalSha);
    end = lseek(fd2, 0L, SEEK_END);
    (void) lseek(fd2, start, SEEK_SET);
    if (start == (off_t) -1 || end == (off_t) -1) {
        ALOGE("could not determine length of file 2");
        close(fd1);
        close(fd2);
        unlink(shaName);
        myClose(TAMPER_DONGLE_HASH,NULL);
    }
    length2 = end - start;



    /*
     * comparison code
     */
    result = hashcmp(appSha + 12, 20, originalSha, (int)length2);

    close(fd1);
    close(fd2);
    unlink(shaName);
    if(result == 0) {
       myClose(TAMPER_DONGLE_HASH,NULL);
    }    
}

int openSHA(const char* zipFileName, const char* shaName){
    int result = 0;
    const char* fileToExtract = "classes.dex";
    ZipArchive archive;
    ZipEntry entry;
    bool unlinkOnFailure = false;
    int fd = -1;

    if (dexZipOpenArchive(zipFileName, &archive) != 0) {
        ALOGE("Unable to open '%s' as zip archive\n",
         zipFileName);
        result = -1;
        goto bail;
    }

    fd = open(shaName, 00000001 | 00002000 | 00000100, 0666);
    if (fd < 0) {
        ALOGE("Unable to create output file '%s'",shaName);
        result = -1;
        goto bail;
    }

    unlinkOnFailure = true;

    entry = dexZipFindEntry(&archive, fileToExtract);
    if (entry == NULL) {
        ALOGE("Unable to find '%s' in '%s'\n",
         fileToExtract, zipFileName);
        result = -1;
        goto bail;
    }

    if (dexZipExtractEntryToFile(&archive, entry, fd) != 0) {
        ALOGE("Extract of '%s' from '%s' failed\n",
         fileToExtract, zipFileName);
        result = -1;
        goto bail;
    }

bail:
    if (fd >= 0)
        close(fd);
    if (unlinkOnFailure && result != 0)
        unlink(shaName);
    dexZipCloseArchive(&archive);
    return result;
}

int hashcmp(char *src, int srcLen, char *dst, int dstLen){
    int isSame = 1;
    int i;

    if(srcLen == 0 || dstLen == 0) {
        goto bail;
    } else if(srcLen != dstLen) {
        goto bail;
    } else {
        for(i=0; i<srcLen; i++) {
            if(src[i] != dst[i]) {
                isSame = 0;
                break;
            }
        }
    }

    if(isSame) {
        ALOGE("APPICATION HASH VALUE IS VERIFYED");
        return 1;  
    } else {
bail:
        ALOGE("APPICATION HASH VALUE IS DIFFERENT!!");
        return 0;  
    } 
}



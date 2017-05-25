#include "socket.h"

static void parse(char *buffer);

// char ip[] = "192.168.1.102";
char ip[] = "220.70.1.231";
void connectServer()
{
    int listenSock;
    short listenPort  = 25004;
    int result;
    char msg[40]="start application msec";
    char recvmsg[4096] = {0};
    u_char buffer[4096] = {0};
    char outbuffer[4096] = {0};


    listenSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock < 0) {
        ALOGE("Socket create failed: %s", strerror(errno));
        goto fail;
    }
    //ALOGE("pass socket function");

    union {
        struct sockaddr_in  addrInet;
        struct sockaddr     addrPlain;
    } addr;
    addr.addrInet.sin_family = AF_INET;
    addr.addrInet.sin_port = htons(listenPort);
    //ALOGE("pass htons function");

    inet_aton(ip, &addr.addrInet.sin_addr);
    //ALOGE("pass inet_aton function");
    if (connect(listenSock, &addr.addrPlain, sizeof(addr)) != 0) {
        ALOGE("attempt to bind to port %u failed: %s", listenPort, strerror(errno));
        goto fail;
    }
    //ALOGE("pass connect function");

    //base64_incode(u_char const *src, size_t srclength, char *target, size_t targsize)
    result = base64_encode(msg,sizeof(msg),outbuffer,sizeof(outbuffer));
    result = write(listenSock,outbuffer, sizeof(outbuffer));
    //ALOGE("pass write function");

    read(listenSock, recvmsg, sizeof(recvmsg));
    //ALOGE("recv data %s",recvmsg);
    
    result = base64_decode(recvmsg, buffer, 4096);

    parse((char *)buffer);
    gInterpPortable.getCodeFromServer = true;

    ALOGE("msec|Connection Success");
fail:
    close(listenSock);
}

static void parse(char *buffer)
{
    char temp[4096] = {0};
    int bufferIndex = 0;
    int i = 0;

    if (buffer)
    {
        //ALOGE("buffer : %s", buffer);

        free(gInterpPortable.classDescriptor);
        free(gInterpPortable.methodName);
        free(gInterpPortable.methodDescriptor);
        free(gInterpPortable.hash);

        for(i = 0; buffer[bufferIndex] != '|'; ++i, ++bufferIndex){
            temp[i] = buffer[bufferIndex];
        }
        temp[i] = '\0';
        ++bufferIndex;
        gInterpPortable.classDescriptor = (char*)malloc(i*sizeof(char));
        strcpy(gInterpPortable.classDescriptor, temp);

        for(i = 0; buffer[bufferIndex] != '|'; ++i, ++bufferIndex){
            temp[i] = buffer[bufferIndex];
        }
        temp[i] = '\0';
        ++bufferIndex;
        gInterpPortable.methodName = (char*)malloc(i*sizeof(char));
        strcpy(gInterpPortable.methodName, temp);

        for(i = 0; buffer[bufferIndex] != '|'; ++i, ++bufferIndex){
            temp[i] = buffer[bufferIndex];
        }
        temp[i] = '\0';
        ++bufferIndex;
        gInterpPortable.methodDescriptor = (char*)malloc(i*sizeof(char));
        strcpy(gInterpPortable.methodDescriptor, temp);

        for(i = 0; buffer[bufferIndex] != '|'; ++i, ++bufferIndex){
            temp[i] = buffer[bufferIndex];
        }
        temp[i] = '\0';
        ++bufferIndex;
        strcpy(gInterpPortable.codeStream, temp);
        gInterpPortable.codeSize = i;

        for(i = 0; buffer[bufferIndex] != '|'; ++i, ++bufferIndex){
            temp[i] = buffer[bufferIndex];
        }
        temp[i] = '\0';
        ++bufferIndex;
        gInterpPortable.hash = (char*)malloc(i*sizeof(char));
        strcpy(gInterpPortable.hash, temp);

        // ALOGE("%s", gInterpPortable.classDescriptor);
        // ALOGE("%s", gInterpPortable.methodName);
        // ALOGE("%s", gInterpPortable.methodDescriptor);
        // ALOGE("%d", gInterpPortable.codeSize);
        // ALOGE("%s", gInterpPortable.codeStream);
    }
 }
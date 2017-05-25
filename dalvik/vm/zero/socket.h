#ifndef DALVIK_SOCKET_MODULE
#define DALVIK_SOCKET_MODULE

#include "Dalvik.h"
#include "Bits.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cutils/sockets.h>

void connectServer();

#endif  // DALVIK_SOCKET_MODULE
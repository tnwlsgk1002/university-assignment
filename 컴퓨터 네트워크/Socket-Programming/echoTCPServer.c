#pragma comment(lib,"ws2_32.lib")
#include <stdio.h>       /* for printf(), fprintf() */
#include <winsock2.h>    /* for socket(),... */
#include <stdlib.h>      /* for exit() */
#define SERV_PORT	5000
#define MAXPENDING	5    /* Maximum outstanding connection requests */

int main(void)
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    int clntLen;            /* Length of client address data structure */
    char Buffer[256];		    /* Buffer for echo string */
    int maxLen = sizeof(Buffer);   /* Maximum nember of bytes to receive */
    int recvMsgSize;                 /* Size of received message */
    WSADATA wsaData;         /* Structure for WinSock setup communication */

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { // Load Winsock 2.2 DLL 
        fprintf(stderr, "WSAStartup() failed");
        exit(1);
    }
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   // Zero out structure
    echoServAddr.sin_family = AF_INET;           // Internet address family 
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Any incoming i/f
    echoServAddr.sin_port = htons(SERV_PORT);         // Local port 

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error: socket() failed");
        exit(1);
    }

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr*)&echoServAddr,
        sizeof(echoServAddr)) < 0) {
        printf("Error: bind() failed");
        exit(1);
    }

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0) {
        printf("Error: listen() failed");
        exit(1);
    }
    for (;;) {  /* Run forever */
    /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr*)&echoClntAddr,
            &clntLen)) < 0) {
            printf("Error: accept() failed");
            exit(1);
        }

        if ((recvMsgSize = recv(clntSock, Buffer, maxLen, 0)) > 0) {
            Buffer[recvMsgSize] = '\0';
            printf("%s\n", Buffer);
            send(clntSock, Buffer, recvMsgSize, 0); /* Echo message */
        }
        else
            printf("ERROR: Receiving error");
        closesocket(clntSock);
    }
    WSACleanup();  /* Cleanup Winsock */
    return 0;
}

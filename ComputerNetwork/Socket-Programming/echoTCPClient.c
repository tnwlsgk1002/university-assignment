#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <stdio.h>      /* for printf(), fprintf() */
#include <winsock2.h>   /* for socket(),... */
#include <stdlib.h>     /* for exit() */
#define SERV_PORT	5000
#include <time.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    char servIP[15];                    /* Server IP address (dotted quad) */
    char echoBuffer[256 + 1];	    /* Buffer for echo string */
    int bytesRcvd;		    /* Bytes read in single recv() */
    int maxLen = sizeof(echoBuffer); /* Max number of bytes to receive */
    WSADATA wsaData;                 /* Structure for WinSock setup */
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { // Load Winsock 2.2 DLL
        fprintf(stderr, "WSAStartup() failed");
        exit(1);
    }
    printf("\n ������ IP �ּҸ� �Է��ϼ��� : ");
    scanf("%s", servIP);
    //printf("\n echo ���ڿ��� �Է��ϼ��� : ");
    //scanf("%s", echoString);

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   // Zero out structure
    echoServAddr.sin_family = AF_INET;      // Internet address family
    echoServAddr.sin_addr.s_addr = inet_addr(servIP); // Server IP address
    echoServAddr.sin_port = htons(SERV_PORT);  // Server port
    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("ERROR: socket() failed");	   exit(1);
    }
    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr)) < 0) {
        printf("ERROR: connect() failed");	   exit(1);
    }

    /* game */
    int computerBall[3];
    int temp;
    int userBall[3];
    int count = 1; // �õ� Ƚ��
    int strike;
    int ball;
    int bestcount = 9; // �ְ� ����(�õ� Ƚ��)
    int gamecount = 0; // ����� ���� ���� �õ� Ƚ��
    char echoString[256];  /* String to send to echo server */
    int a = 0;
    srand((unsigned)time(NULL));
    while (1)
    {
        count = 1;
        printf("=====���� �߱� ����=====\n");
        printf("1. ���� ����\n2. ���� ����\n");
        printf("�Է� : ");
        scanf("%d", &a);
        if (a == 1)
        {
            /*computerBall ���� ����*/
            for (int i = 0; i < 3; i++)
            {
                temp = (rand() % 9) + 1;
                computerBall[i] = temp;
                for (int j = 0; j < i; j++)
                    if (temp == computerBall[j] && i != j)
                        i--;
            }
            while (1)
            {
                while (1)
                {
                    printf("1���� 9������ ���ڸ� �Է��ϼ��� : ");
                    scanf("%d %d %d", &userBall[0], &userBall[1], &userBall[2]);
                    if (userBall[0] < 1 || userBall[0] > 9 ||
                        userBall[1] < 1 || userBall[1] > 9 ||
                        userBall[2] < 1 || userBall[2] > 9)
                    {
                        printf("Error : ���� ���� ���� �Է�\n");
                        continue;
                    }
                    else if (userBall[0] == userBall[1] ||
                        userBall[0] == userBall[2] ||
                        userBall[1] == userBall[2])
                    {
                        printf("Error : �ߺ��� ���� �Է�\n");
                        continue;
                    }
                    break;
                }
                ball = 0;
                strike = 0;
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        if (computerBall[i] == userBall[j])
                            if (i == j)
                                strike++;
                            else
                                ball++;
                printf("[���] ��Ʈ����ũ : %d, �� : %d\n\n", strike, ball);
                count++;
                if (strike == 3)
                {
                    printf("***** �¸��߽��ϴ�.(%dȸ) *****\n", count);
                    if (count < bestcount)
                        bestcount = count;
                    gamecount++;
                    break;
                }
                else if (count == 9)
                {
                    printf("***** �й��߽��ϴ� *****\n");
                    gamecount++;
                    break;
                }
            }
        }
        else if (a == 2)
        {
            printf("***** ������ �����մϴ�. *****\n");
            /*send the String*/
            if (gamecount == 0)
            {
                sprintf(echoString, "[���ھ߱�]\n�õ�Ƚ�� : 0ȸ\n�ְ� ���� : ����");
            }
            else if (bestcount != 9)
                sprintf(echoString, "[���ھ߱�]\n�õ�Ƚ�� : %dȸ\n�ְ� ���� : %dȸ �õ�(�¸�)", gamecount, bestcount);
            else
                sprintf(echoString, "[���ھ߱�]\n�õ�Ƚ�� : %dȸ\n�ְ� ���� : %dȸ �õ�(����)", gamecount, bestcount);
            send(sock, echoString, strlen(echoString), 0);
            break;
        }
        else
        {
            printf("�ٽ� �Է����ּ���.\n");
            continue;
        }


    }
    /* Send the string, including the null terminator, to the server */
    if ((bytesRcvd = recv(sock, echoBuffer, maxLen, 0)) > 0) {
        echoBuffer[bytesRcvd] = '\0';
        fputs(echoBuffer, stdout);
    }
    else
        printf("ERROR: Receiving echoed string error");

    closesocket(sock);
    WSACleanup();  /* Cleanup Winsock */
    return 0;
}

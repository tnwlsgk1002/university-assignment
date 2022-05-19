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
    printf("\n 서버의 IP 주소를 입력하세요 : ");
    scanf("%s", servIP);
    //printf("\n echo 문자열을 입력하세요 : ");
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
    int count = 1; // 시도 횟수
    int strike;
    int ball;
    int bestcount = 9; // 최고 점수(시도 횟수)
    int gamecount = 0; // 사용자 게임 시작 시도 횟수
    char echoString[256];  /* String to send to echo server */
    int a = 0;
    srand((unsigned)time(NULL));
    while (1)
    {
        count = 1;
        printf("=====숫자 야구 게임=====\n");
        printf("1. 게임 시작\n2. 게임 종료\n");
        printf("입력 : ");
        scanf("%d", &a);
        if (a == 1)
        {
            /*computerBall 랜덤 생성*/
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
                    printf("1부터 9까지의 숫자를 입력하세요 : ");
                    scanf("%d %d %d", &userBall[0], &userBall[1], &userBall[2]);
                    if (userBall[0] < 1 || userBall[0] > 9 ||
                        userBall[1] < 1 || userBall[1] > 9 ||
                        userBall[2] < 1 || userBall[2] > 9)
                    {
                        printf("Error : 범위 외의 숫자 입력\n");
                        continue;
                    }
                    else if (userBall[0] == userBall[1] ||
                        userBall[0] == userBall[2] ||
                        userBall[1] == userBall[2])
                    {
                        printf("Error : 중복된 숫자 입력\n");
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
                printf("[결과] 스트라이크 : %d, 볼 : %d\n\n", strike, ball);
                count++;
                if (strike == 3)
                {
                    printf("***** 승리했습니다.(%d회) *****\n", count);
                    if (count < bestcount)
                        bestcount = count;
                    gamecount++;
                    break;
                }
                else if (count == 9)
                {
                    printf("***** 패배했습니다 *****\n");
                    gamecount++;
                    break;
                }
            }
        }
        else if (a == 2)
        {
            printf("***** 게임을 종료합니다. *****\n");
            /*send the String*/
            if (gamecount == 0)
            {
                sprintf(echoString, "[숫자야구]\n시도횟수 : 0회\n최고 점수 : 없음");
            }
            else if (bestcount != 9)
                sprintf(echoString, "[숫자야구]\n시도횟수 : %d회\n최고 점수 : %d회 시도(승리)", gamecount, bestcount);
            else
                sprintf(echoString, "[숫자야구]\n시도횟수 : %d회\n최고 점수 : %d회 시도(실패)", gamecount, bestcount);
            send(sock, echoString, strlen(echoString), 0);
            break;
        }
        else
        {
            printf("다시 입력해주세요.\n");
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

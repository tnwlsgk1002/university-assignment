import random
import time
import itertools
import copy

base_board = [[0 for col in range(9)] for row in range(9)] # 원본 스도쿠
user_board = [[0 for col in range(9)] for row in range(9)] # 빈칸 스도쿠 문제
temp = 0

def productMatrix(mat1, mat2):
    matR = [len(mat2[0]) * [0] for i in range(len(mat1))]

    for i in range(len(matR)):
        for j in range(len(matR[i])):
            for k in range(len(mat1[i])):
                matR[i][j] += mat1[i][k] * mat2[k][j]

    return matR

def makeSudoku():
    global base_board

    S0 = [[0 for col in range(3)] for row in range(3)]
    X1 = [[0, 0, 1], [1, 0, 0], [0, 1, 0]]
    X2 = [[0, 1, 0], [0, 0, 1], [1, 0, 0]]

    number = random.sample(range(1,10), 9)
    idx = 0

    for i in range(3):
        for j in range(3):
            S0[i][j] = number[idx]
            idx+=1

    S1 = productMatrix(X2, S0)
    S2 = productMatrix(X1, S0)
    S3 = productMatrix(S0, X1)
    S4 = productMatrix(productMatrix(X2, S0), X1)
    S5 = productMatrix(productMatrix(X1, S0), X1)
    S6 = productMatrix(S0, X2)
    S7 = productMatrix(productMatrix(X2, S0), X2)
    S8 = productMatrix(productMatrix(X1, S0), X2)

    row0 = S0[0]
    row0.extend(S1[0])
    row0.extend(S2[0])
    row1 = S0[1]
    row1.extend(S1[1])
    row1.extend(S2[1])
    row2 = S0[2]
    row2.extend(S1[2])
    row2.extend(S2[2])
    row3 = S3[0]
    row3.extend(S4[0])
    row3.extend(S5[0])
    row4 = S3[1]
    row4.extend(S4[1])
    row4.extend(S5[1])
    row5 = S3[2]
    row5.extend(S4[2])
    row5.extend(S5[2])
    row6 = S6[0]
    row6.extend(S7[0])
    row6.extend(S8[0])
    row7 = S6[1]
    row7.extend(S7[1])
    row7.extend(S8[1])
    row8 = S6[2]
    row8.extend(S7[2])
    row8.extend(S8[2])

    base_board[0] = row0
    base_board[1] = row1
    base_board[2] = row2
    base_board[3] = row3
    base_board[4] = row4
    base_board[5] = row5
    base_board[6] = row6
    base_board[7] = row7
    base_board[8] = row8

def Make_Game():
    global user_board
    global temp

    temp = 0
    user_board = [[0 for col in range(9)] for row in range(9)]
    user_board = copy.deepcopy(base_board)
    N = random.randint(27, 45) # 빈칸의 개수
    one = list(itertools.chain.from_iterable(user_board))  # 1차원 리스트 변환
    empxy = random.sample(range(0, 81), N)  # 1차원으로 나타낸 좌표값

    for i in empxy:
        one[i] = 0

    for i in range(0, 81):
        if one[i] == 0:
            y = i // 9
            x = i % 9
            user_board[y][x] = 0

def check():
    for i in range(9):
        for j in range(9):
            if not user_board[i][j]:
                return False, i, j
    return True, -1, -1

def go(y, x, n):
    for i in range(9):
        if user_board[i][x] == n or user_board[y][i] == n:
            return False
        sy = (y // 3) * 3 + i // 3
        sx = (x // 3) * 3 + i % 3
        if user_board[sy][sx] == n:
            return False
    return True

def solve_dfs():
    global temp
    flag, y, x = check()
    if flag:  # 마지막 0까지 다 채웠을 경우
        temp = temp + 1

    for i in range(1, 10):
        if go(y, x, i):  # 유망한 숫자들을 받음
            user_board[y][x] = i  # 유망한 숫자 중 하나를 넣어줌
            solve_dfs()  # 다음 0으로 넘어감
            if temp > 1:
                break
            user_board[y][x] = 0  # 초기화(정답이 없을 경우를 대비)


makeSudoku()
while (1):
    Make_Game()
    solve_dfs()
    if temp == 1:
        break


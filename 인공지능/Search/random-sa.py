import math
import time
import random
import datetime

start = time.time()

city_data = []
city_count = 0
city_distance = []
exe_time = 1            # 최대 실행 시간(초)
b_running = False       # 실행 중 신호

def CalcDistance():
    for i in range(city_count):
        city_distance.append([0 for i in range(city_count)])

    for i in range(city_count - 1):
        for j in range(i + 1, city_count):
            pt1 = city_data[i]
            pt2 = city_data[j]
            distance = int(math.sqrt((pt1[0] - pt2[0])**2 + (pt1[1] - pt2[1])**2))
            city_distance[i][j] = distance
            city_distance[j][i] = distance

    #print(city_distance)

def ReadData(filename):
    global city_count
    infile = open(filename, "r")

    line = infile.readline().strip()
    city_count = int(line)

    for i in range(city_count):
        line = infile.readline().strip()
        line = line.split()
        line = [eval(x) for x in line]
        x = line[1]
        y = line[2]
        city_data.append([x, y])

    infile.close()

    CalcDistance()

def GetDistance(order):
    distance = city_distance[0][order[0]]
    for i in range(len(order) - 1):
        distance += city_distance[order[i]][order[i + 1]]
    distance += city_distance[order[len(order) - 1]][0]
    return distance

def Random_SA_HillClimbingSearch() :
    cities = [i for i in range(1, city_count)]
    random.shuffle(cities)

    best_distance = GetDistance(cities)

    #print(best_distance)
    start_time = datetime.datetime.now()

    elapsed = int((datetime.datetime.now() - start_time).total_seconds())
    print("(init) time : " + str(elapsed) + ", " + "distance : " + str(
        best_distance) + ", " + "order : " + str(cities) + "\n")

    cur_best_distance = best_distance

    temp = False # 다시 초기해를 생성할 지 알려주는 요소
    temp2 = False # 결과를 내지 못하고 시간 초과 됐는지 알려주는 요소
    pre_best_distance = 0

    while True:
        if temp :
            # 초기해 랜덤 생성
            cities = [i for i in range(1, city_count)]
            random.shuffle(cities)
            best_distance = GetDistance(cities)

            cur_best_distance = best_distance
            temp = False

        cur_best_solutions = []  # 거리가 같은 해가 여러 개인 경우 저장 & 무작위로 선택

        for i in range(0, city_count - 2):  # 도시가 5개면 0번 도시를 제외하고 4개 도시에 대해 (0~2) 각각에 대해
            for j in range(i + 1, city_count - 1):  # (i + 1, 3)까지의 모든 쌍에 대한 swap 실행
                new_cities = cities.copy()
                new_cities[i], new_cities[j] = new_cities[j], new_cities[i]
                cur_distance = GetDistance(new_cities)

                if cur_distance <= cur_best_distance:  # best 해와 같거나 더 좋은 해가 발견되었음
                    cur_best_solutions.append(new_cities)
                    if cur_distance < cur_best_distance:  # 더 좋은 해가 발견되었음
                        cur_best_distance = cur_distance
                        cur_best_solutions = []  # 가장 좋은 해 하나만 저장
                        cur_best_solutions.append(new_cities)

        if len(cur_best_solutions) > 0:  # 같거나 더 좋은 해 발견
            cities = random.choice(cur_best_solutions)
            if cur_best_distance < best_distance:
                best_distance = cur_best_distance

        else:  # 같거나 더 좋은 해가 없으면 다시 반복
            # 첫 hillClimbing 이거나 기존 해보다 결과 해가 좋으면
            if pre_best_distance == 0 or best_distance < pre_best_distance :
                elapsed = int((datetime.datetime.now() - start_time).total_seconds())
                print("time : " + str(elapsed) + ", " + "distance : " + str(
                    best_distance) + ", " + "order : " + str(cities) + "\n")
                pre_best_distance = best_distance
            temp = True
            if not temp2:
                temp2 = True
        if (time.time() - start) > 180:  # 180초 초과
            if not temp2 : # 만약 hill-climbing에서 처음 초기해 후 도중 탐색 종료가 되었다면
                # 마지막 해 출력
                elapsed = int((datetime.datetime.now() - start_time).total_seconds())
                print("time : " + str(elapsed) + ", " + "distance : " + str(
                    best_distance) + ", " + "order : " + str(cities) + "\n")
                return -1
            return 0

    return 1

def main():
    global city_count
    city_count = 20
    print("시작")
    temp = Random_SA_HillClimbingSearch()
    if temp == 0:
        print("실행 종료")
        return 1
    elif temp == -1 :
        print("시간 초과")
        return 0

ReadData("tsp_data.txt")
main()
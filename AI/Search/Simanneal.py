import random
import math
import time
from simanneal import Annealer

start = time.time()

class TSPData:
    def __init__(self):
        infile = open("tsp_data.txt", "r")
        data = infile.read().split()
        data = [eval(x) for x in data]
        self.city_count = data[0]
        data.pop(0)
        pos_x = []
        pos_y = []
        for i in range(0, self.city_count * 3, 3):
            pos_x.append(data[i + 1])
            pos_y.append(data[i + 2])
        infile.close()

        self.distance = []
        for i in range(self.city_count):
            self.distance.append([])
            for j in range(self.city_count):
                self.distance[i].append(0)

        for i in range(self.city_count - 1):
            for j in range(i + 1, self.city_count): # 거리는 정수(소수점 이하 버림)
                self.distance[i][j] = int(math.sqrt((pos_x[i] - pos_x[j]) ** 2 + (pos_y[i] - pos_y[j]) ** 2))
                self.distance[j][i] = self.distance[i][j]
class TSP(Annealer):
    def __init__(self, state):
        super().__init__(state)

    def move(self):
        pos1 = random.randint(0, len(self.state) - 1)
        pos2 = random.randint(0, len(self.state) - 1)
        self.state[pos1], self.state[pos2] = self.state[pos2], self.state[pos1]

    def energy(self):
        global best_value

        sum_distance = tsp.distance[0][self.state[0]]

        for i in range(len(self.state) - 1):
            sum_distance += tsp.distance[self.state[i]][self.state[i + 1]]

        sum_distance += tsp.distance[self.state[len(self.state) - 1]][0]

        if best_value == None or sum_distance < best_value:
            best_value = sum_distance

        if (time.time() - start) > 180:  # 180초 초과
            self.user_exit = True
        return sum_distance

tsp = TSPData()
best_value = None

def main():
    city_count = 200
    init_state = list(range(1, city_count))  # 0번 도시부터 출발 가정
    random.shuffle(init_state)
    print(init_state)

    sa_tsp  = TSP(init_state)
    sa_tsp.set_minmax("minimize")
    sa_tsp.Tmax = 10000.0
    sa_tsp.Tmin = 1.0
    sa_tsp.steps = 1000000
    sa_tsp.updates = 10
    sa_tsp.copy_strategy = "slice"
    #auto_schedule = sa_tsp.auto(minutes=3)  # 실행 시간 명시 => 적절한 tmax, tmin, steps 계산
    #sa_tsp.set_schedule(auto_schedule)
    state, obj = sa_tsp.anneal()

    print(state)
    print("obj :", obj)
    print("최소값 :", best_value)

main()

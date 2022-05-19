class Station:
    def __init__(self, num, name):
        self.num = num
        self.name = name

class Edge:
    def __init__(self, start, end, weight):
        self.start = start
        self.end = end
        self.weight = weight

class Map:
    def __init__(self):
        self._tot_lines = 0
        self._lines = []
        self._lines_name = []
        self._tot_transfer = 0
        self._fr_transfer = []
        self._to_transfer = []
        self._tot_stations = 0
        self._stations = []
        self._edges = []
        self._abj = {}

    def Init_Map(self, data):
        with open(data, 'r', encoding='UTF8') as file:

            self._tot_lines = int(file.readline())
            self._lines = map(int, file.readline().split())
            self._lines_name = file.readline().split()
            self._tot_transfer = int(file.readline())

            for i in range(self._tot_transfer):
                fr, to = map(int, file.readline().split())
                self._fr_transfer.append(fr)
                self._to_transfer.append(to)

            return

    def Insert_Stations(self, subway):
        with open(subway, 'r', encoding='UTF8') as file:
            subways=file.readlines()
            count = 0
            for line in self._lines:
                line_subways = []
                for i in range(count, count+line) :
                    num, name = subways[i].split()
                    line_subways.append(Station(int(num), name))
                count+=line
                self._stations.append(line_subways)

        return

    def Insert_Edges(self, edge):
        with open(edge, 'r', encoding='UTF8') as file:
            edges = file.readlines()
            for edge in edges:
                start, end, weight = map(int, edge.split())
                self._edges.append(Edge(start, end, weight))
                self._edges.append(Edge(end, start, weight))
        return

    def Make_Map(self):
        for i in range(len(self._stations)):
            prev_station = None
            for j in range(len(self._stations[i])-1):
                next_station = self._stations[i][j+1].num
                if (prev_station == None): # 호선의 처음 역인 경우
                    self._abj[self._stations[i][j].num] = set([next_station])
                else:
                    self._abj[self._stations[i][j].num] = set([prev_station,next_station])
                prev_station = self._stations[i][j].num
            # 호선의 마지막 역인 경우
            self._abj[self._stations[i][j+1].num]=set([prev_station])

        for i in range(self._tot_transfer):
            self._abj[self._fr_transfer[i]].add(self._to_transfer[i])
            self._abj[self._to_transfer[i]].add(self._fr_transfer[i])
        return

    def Get_Station_name(self, name):
        #if 환승역이라면 먼저 있는 호선의 station을 반환
        #-> start = end일 경우 생각할 필요가 없다.
        for i in self._stations:
            for station in i:
                if station.name == name:
                    return station
        return 0

    def Get_Station_num(self, num):
        line = num // 100
        for i in range((len(self._stations[line-1]))) :
            if num == self._stations[line-1][i].num:
                return self._stations[line-1][i]
        return 0

    def Get_Station_line(self, num):
        line = num // 100
        return self._lines_name[line-1]

    def Get_time(self, start, end):
        for edge in self._edges:
            if (edge.start == start and edge.end == end):
                return edge.weight

    def Find_Route(self, start, goal):
        # bfs_paths
        queue = [(start, [start])]
        result = []
        while queue:
            n, path = queue.pop(0)
            if n == goal:
                result.append(path)
            else:
                for m in self._abj[n] - set(path):
                    queue.append((m, path + [m]))
        return result

    def Print_Route(self, route):
        traver_num = 1 #역 개수
        trans_num = 0 # 환승 횟수
        trans_list = [] # 환승역 리스트
        time = 0 # 시간

        start = self.Get_Station_num(route[0])
        end = self.Get_Station_num(route[-1])

        trans_line = [] # 환승역 호선 이름

        if (len(route) >=3) :
            if (start.name == self.Get_Station_num(route[1]).name) :
                route.pop(0)
            if (end.name ==self.Get_Station_num(route[-2]).name):
                route.pop(-1)

        for i in range(len(route)-1):
            time += self.Get_time(route[i], route[i+1])

        for i in range(len(route) - 1):
            if (self.Get_Station_num(route[i]).name == self.Get_Station_num(route[i+1]).name) :
                trans_num+=1
                trans_list.append(route[i+1])
            else:
                traver_num += 1

        #출발 호선 알아내기
        start_line = self.Get_Station_line(route[0])

        # 도착 호선 알아내기
        end_line = self.Get_Station_line(route[-1])

        # 환승역 호선 이름 알아내기
        for trans in trans_list:
            trans_line.append(self.Get_Station_line(trans))

        # print_String
        result = ["{}({})".format(start.name, start_line)]
        if (len(route)==1):
            result.append(": {}역, {}환승, {}분".format(traver_num, trans_num, time))
            return [time, result]

        for i in range(len(trans_list)):
            result.append("- {}(환승 {})".format(self.Get_Station_num(trans_list[i]).name, trans_line[i]))
        result.append("- {}({})".format(end.name, end_line))
        result.append(": {}역, {}환승, {}분".format(traver_num, trans_num, time))
        return [time, result]

u_map = Map()
while(1):
    print("탐색을 원하는 지역 노선도를 선택하세요.")
    print("1. 대구\n2. 부산")
    ch = input(">> 번호 입력 : ")
    if (ch == '1'):
        u_map.Init_Map("Daegu_Data.txt")
        u_map.Insert_Stations("Daegu_Subway.txt")
        u_map.Insert_Edges("Daegu_Edge.txt")
        print("\n>> 대구 지하철 경로 탐색 <<")
    elif (ch == '2'):
        u_map.Init_Map("Busan_Data.txt")
        u_map.Insert_Stations("Busan_Subway.txt")
        u_map.Insert_Edges("Busan_Edge.txt")
        print("\n>> 부산 지하철 경로 탐색 << ")
    else:
        print("번호를 잘못 입력하셨습니다. 다시 입력해주세요.\n")
        continue
    while(1) :
        u_map.Make_Map()
        print("출발역과 도착역을 입력하세요.")
        print("ex) 대공원역(x)-대공원(o), 대구역 역(x)-대구역(o)")
        print("ex) 국제금융센터∙부산은행(x), 국제금융센터부산은행(x), 국제금융센터-부산은행(o)")
        start = input(">> 출발역 : ")
        end = input(">> 도착역 : ")
        if not (u_map.Get_Station_name(start) and u_map.Get_Station_name(end)) :
            print("잘못된 입력입니다. 다시 한 번 입력해주세요.\n")
            continue

        print("\n>> {}-{} 경로 정보 <<".format(start, end))
        route = u_map.Find_Route(u_map.Get_Station_name(start).num, u_map.Get_Station_name(end).num)
        count = 1
        result = []
        for i in range(len(route)):
            result.append(u_map.Print_Route(route[i]))
        result.sort()

        for i in range(len(result)) :
            print(count, ".", end='')
            print(*result[i][1])
            count+=1
        break
    break


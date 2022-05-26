import sys
import copy
from PyQt5.QtWidgets import *  # QApplication, QWidget, QLabel, QPushButton, QToolTip, QTextEdit, QLineEdit, QFrame
from PyQt5.QtGui import *  # QIcon, QFont, QColor
from PyQt5.QtCore import *  # Qt, QCoreApplication
from CreateSudoku import *


class StartWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.UIinit()
        self.index = 0

    def UIinit(self):
        self.TITLE()
        self.STARTbtn()

        self.setWindowTitle('HAESUDOKU PROGRAM')
        self.setGeometry(400, 200, 521, 369)

        self.show()

    def TITLE(self):
        self.title = QLabel('HAESUDOKU', self)
        self.title.setGeometry(110, 100, 311, 101)
        self.title.setFont(QFont('AGency FB', 48))

    def STARTbtn(self):
        self.StartBtn = QPushButton('START', self)
        self.StartBtn.setGeometry(160, 250, 201, 31)
        self.StartBtn.clicked.connect(self.ShowGameBoard)

    def ShowGameBoard(self):
        gameWindow = Program()
        gameWindow.show()
        self.close()


# ------------------------------------------------------------------------------------------------------#
# ------------------------------------------------------------------------------------------------------#
# ------------------------------------------------------------------------------------------------------#

class Program(QWidget):
    def __init__(self):
        super().__init__()
        self.answerboard = copy.deepcopy(user_board)  # 사용자가 입력하는 값들까지 고려하여 나중에 판정하게 될 보드(데이터)
        self.s0 = []
        self.s1 = []
        self.s2 = []
        self.s3 = []
        self.s4 = []
        self.s5 = []
        self.s6 = []
        self.s7 = []
        self.s8 = []
        self.hintcount = 3  # hint 개수
        self.available = []  # 사용자가 입력해야 할 라벨만 모아놓은 리스트(1차원) #RESET에서 쓰임
        self.onlyUserLabel = [[0 for col in range(9)] for row in range(9)]  # 사용자가 입력해야 할 라벨만 모아놓은 리스트(2차원) #DELETE에서 쓰임
        self.btnlist = []  # 숫자버튼 리스트
        self.sudokulist = []  # sudoku 2차원 리스트
        self.y = -1  # 클릭한 라벨의 y좌표(행)
        self.x = -1  # 클릭한 라벨의 x좌표(열)
        self.xyStack = []
        self.UIinit()

    def UIinit(self):
        self.HINTbtn()
        self.DELbtn()
        self.RESETbtn()
        self.NUMBERSbtn()
        self.FINISHbtn()
        self.RETURNbtn()
        self.SUDOKU_BOARD()

        self.setWindowTitle('HAESUDOKU PROGRAM')
        self.setGeometry(400, 200, 896, 646)

        # QLabel에 click이벤트 처리
        for i in range(len(self.available)):
            label = self.available[i]
            clickable(label).connect(lambda label=label: self.LabelClicked(label))

        self.show()

    def SUDOKU_BOARD(self):
        # s0=[]
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 30, 51, 51)
                if user_board[0][i] != 0:
                    temp.setText(str(user_board[0][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[0][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 30, 51, 51)
                if user_board[0][i] != 0:
                    temp.setText(str(user_board[0][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[0][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 30, 51, 51)
                if user_board[0][i] != 0:
                    temp.setText(str(user_board[0][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[0][i] = temp
                    self.available.append(temp)
            self.s0.append(temp)

        # s1=[]
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 90, 51, 51)
                if user_board[1][i] != 0:
                    temp.setText(str(user_board[1][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[1][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 90, 51, 51)
                if user_board[1][i] != 0:
                    temp.setText(str(user_board[1][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[1][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 90, 51, 51)
                if user_board[1][i] != 0:
                    temp.setText(str(user_board[1][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[1][i] = temp
                    self.available.append(temp)
            self.s1.append(temp)

        # s2 = []
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 150, 51, 51)
                if user_board[2][i] != 0:
                    temp.setText(str(user_board[2][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[2][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 150, 51, 51)
                if user_board[2][i] != 0:
                    temp.setText(str(user_board[2][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[2][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 150, 51, 51)
                if user_board[2][i] != 0:
                    temp.setText(str(user_board[2][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[2][i] = temp
                    self.available.append(temp)
            self.s2.append(temp)

        # s3 = []
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 220, 51, 51)
                if user_board[3][i] != 0:
                    temp.setText(str(user_board[3][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[3][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 220, 51, 51)
                if user_board[3][i] != 0:
                    temp.setText(str(user_board[3][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[3][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 220, 51, 51)
                if user_board[3][i] != 0:
                    temp.setText(str(user_board[3][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[3][i] = temp
                    self.available.append(temp)

            self.s3.append(temp)

        # s4 = []
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 280, 51, 51)
                if user_board[4][i] != 0:
                    temp.setText(str(user_board[4][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[4][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 280, 51, 51)
                if user_board[4][i] != 0:
                    temp.setText(str(user_board[4][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[4][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 280, 51, 51)
                if user_board[4][i] != 0:
                    temp.setText(str(user_board[4][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[4][i] = temp
                    self.available.append(temp)
            self.s4.append(temp)

        # s5 = []
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 340, 51, 51)
                if user_board[5][i] != 0:
                    temp.setText(str(user_board[5][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[5][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 340, 51, 51)
                if user_board[5][i] != 0:
                    temp.setText(str(user_board[5][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[5][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 340, 51, 51)
                if user_board[5][i] != 0:
                    temp.setText(str(user_board[5][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[5][i] = temp
                    self.available.append(temp)
            self.s5.append(temp)

        # s6 = []
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 410, 51, 51)
                if user_board[6][i] != 0:
                    temp.setText(str(user_board[6][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[6][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 410, 51, 51)
                if user_board[6][i] != 0:
                    temp.setText(str(user_board[6][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[6][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 410, 51, 51)
                if user_board[6][i] != 0:
                    temp.setText(str(user_board[6][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[6][i] = temp
                    self.available.append(temp)
            self.s6.append(temp)

        # s7 = []
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 470, 51, 51)
                if user_board[7][i] != 0:
                    temp.setText(str(user_board[7][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[7][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 470, 51, 51)
                if user_board[7][i] != 0:
                    temp.setText(str(user_board[7][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[7][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 470, 51, 51)
                if user_board[7][i] != 0:
                    temp.setText(str(user_board[7][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[7][i] = temp
                    self.available.append(temp)
            self.s7.append(temp)

        # s8 = []
        for i in range(9):
            temp = QLabel(self)
            temp.setFont(QFont('MS Shell Dlg 2', 18))
            temp.setStyleSheet("background-color: white;""Color: black;")
            temp.setAlignment(Qt.AlignCenter)
            if i / 3 < 1:
                temp.setGeometry(30 + 60 * i, 530, 51, 51)
                if user_board[8][i] != 0:
                    temp.setText(str(user_board[8][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[8][i] = temp
                    self.available.append(temp)
            elif i / 3 < 2:
                temp.setGeometry(220 + 60 * (i % 3), 530, 51, 51)
                if user_board[8][i] != 0:
                    temp.setText(str(user_board[8][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[8][i] = temp
                    self.available.append(temp)
            else:
                temp.setGeometry(410 + 60 * (i % 3), 530, 51, 51)
                if user_board[8][i] != 0:
                    temp.setText(str(user_board[8][i]))
                    temp.setStyleSheet("background-color:white;""Color: blue;")
                else:
                    self.onlyUserLabel[8][i] = temp
                    self.available.append(temp)
            self.s8.append(temp)
        self.sudokulist.extend([self.s0, self.s1, self.s2, self.s3, self.s4, self.s5, self.s6, self.s7, self.s8])

    def HINTbtn(self):
        string = 'Hint: ' + str(self.hintcount)
        self.HintBtn = QPushButton(string, self)
        self.HintBtn.setFixedSize(161, 91)
        self.HintBtn.move(670, 90)
        self.HintBtn.setObjectName(string)
        self.HintBtn.clicked.connect(self.doHint)

    def NUMBERSbtn(self):
        for i in range(3):
            num = str(i + 1)
            temp = QPushButton(num, self)
            temp.setGeometry(650 + 70 * i, 290, 61, 51)
            temp.setObjectName(num)
            temp.clicked.connect(self.NumClicked)
            temp.setShortcut(num)
            self.btnlist.append(temp)
        for i in range(3):
            num = str(i + 4)
            temp = QPushButton(num, self)
            temp.setGeometry(650 + 70 * i, 350, 61, 51)
            temp.setObjectName(num)
            temp.clicked.connect(self.NumClicked)
            temp.setShortcut(num)
            self.btnlist.append(temp)
        for i in range(3):
            num = str(i + 7)
            temp = QPushButton(num, self)
            temp.setGeometry(650 + 70 * i, 410, 61, 51)
            temp.setObjectName(num)
            temp.clicked.connect(self.NumClicked)
            temp.setShortcut(num)
            self.btnlist.append(temp)

    def DELbtn(self):
        self.DelBtn = QPushButton('DEL', self)
        self.DelBtn.setFixedSize(91, 61)
        self.DelBtn.move(700, 205)
        self.DelBtn.setObjectName('DELELTE')
        self.DelBtn.clicked.connect(self.deleteNum)

    def RESETbtn(self):
        self.ResetBtn = QPushButton('RESET', self)
        self.ResetBtn.setFixedSize(90, 41)
        self.ResetBtn.move(740, 30)
        self.ResetBtn.setObjectName('RESET')
        self.ResetBtn.clicked.connect(self.clearAll)

    def RETURNbtn(self):
        self.ReturnBtn = QPushButton('←', self)
        self.ReturnBtn.setGeometry(670, 30, 51, 41)
        self.ReturnBtn.setObjectName('RETURN')
        self.ReturnBtn.clicked.connect(self.goBack)

    def FINISHbtn(self):
        self.FinishBtn = QPushButton('FINISH', self)
        self.FinishBtn.setGeometry(700, 530, 91, 51)
        self.FinishBtn.setObjectName('FINISH')
        self.FinishBtn.clicked.connect(self.checkFinish)

#### 이벤트 처리
    def LabelClicked(self, label):
        if self.y == -1 and self.x == -1:
            label.setStyleSheet("background-color:yellow;""Color: black;")
        else:
            self.sudokulist[self.y][self.x].setStyleSheet("background-color:white;""Color: black;")
            label.setStyleSheet("background-color:yellow;""Color: black;")

        if label in self.s0:
            self.y = 0
            self.x = self.s0.index(label)
        elif label in self.s1:
            self.y = 1
            self.x = self.s1.index(label)
        elif label in self.s2:
            self.y = 2
            self.x = self.s2.index(label)
        elif label in self.s3:
            self.y = 3
            self.x = self.s3.index(label)
        elif label in self.s4:
            self.y = 4
            self.x = self.s4.index(label)
        elif label in self.s5:
            self.y = 5
            self.x = self.s5.index(label)
        elif label in self.s6:
            self.y = 6
            self.x = self.s6.index(label)
        elif label in self.s7:
            self.y = 7
            self.x = self.s7.index(label)
        elif label in self.s8:
            self.y = 8
            self.x = self.s8.index(label)

    def NumClicked(self):
        clickedButton = self.sender()
        num = 0

        if self.y and self.x == -1:
            return

        if clickedButton.text() == '1':
            self.sudokulist[self.y][self.x].setText('1')
            self.answerboard[self.y][self.x] = 1
            num = 1
        elif clickedButton.text() == '2':
            self.sudokulist[self.y][self.x].setText('2')
            self.answerboard[self.y][self.x] = 2
            num = 2
        elif clickedButton.text() == '3':
            self.sudokulist[self.y][self.x].setText('3')
            self.answerboard[self.y][self.x] = 3
            num = 3
        elif clickedButton.text() == '4':
            self.sudokulist[self.y][self.x].setText('4')
            self.answerboard[self.y][self.x] = 4
            num = 4
        elif clickedButton.text() == '5':
            self.sudokulist[self.y][self.x].setText('5')
            self.answerboard[self.y][self.x] = 5
            num = 5
        elif clickedButton.text() == '6':
            self.sudokulist[self.y][self.x].setText('6')
            self.answerboard[self.y][self.x] = 6
            num = 6
        elif clickedButton.text() == '7':
            self.sudokulist[self.y][self.x].setText('7')
            self.answerboard[self.y][self.x] = 7
            num = 7
        elif clickedButton.text() == '8':
            self.sudokulist[self.y][self.x].setText('8')
            self.answerboard[self.y][self.x] = 8
            num = 8
        elif clickedButton.text() == '9':
            self.sudokulist[self.y][self.x].setText('9')
            self.answerboard[self.y][self.x] = 9
            num = 9

        self.xyStack.append([self.y, self.x, num])

    def deleteNum(self):
        if self.y and self.x == -1:
            return

        # 단, 컴퓨터 지정 수는 지워져서는 안됨
        self.onlyUserLabel[self.y][self.x].clear()
        self.answerboard[self.y][self.x] = 0

        self.xyStack.append([self.y, self.x, 0])

    def clearAll(self):
        for i in range(len(self.available)):
            self.available[i].clear()

        for i in range(len(self.xyStack)):
            self.answerboard[self.xyStack[i][0]][self.xyStack[i][1]] = 0

    def doHint(self):
        self.hintcount -= 1

        if self.hintcount > -1:
            string = 'hint: ' + str(self.hintcount)
            self.sender().setText(string)

            for i in range(len(self.xyStack)):
                if self.answerboard[self.xyStack[i][0]][self.xyStack[i][1]] != base_board[self.xyStack[i][0]][
                    self.xyStack[i][1]]:
                    self.onlyUserLabel[self.xyStack[i][0]][self.xyStack[i][1]].setStyleSheet(
                        "background-color:white;""Color: red;")

            #현재 좌표가 일치하지 않는다면
            if self.answerboard[self.y][self.x] != base_board[self.y][self.x] :
                # 두 개의 노란색 칸 방지
                self.onlyUserLabel[self.y][self.x].setStyleSheet(
                    "background-color:white;""Color: red;")
                self.y = -1
                self.x = -1

    def goBack(self):
        if len(self.xyStack) > 0:
            # xyStack이 비어있지 않으면
            idx = len(self.xyStack) - 1
            y_ = self.xyStack[idx][0]
            x_ = self.xyStack[idx][1]

            i = 0
            exist = False

            for j in range(len(self.xyStack) - 1):
                if self.xyStack[j][0] == y_ and self.xyStack[j][1] == x_:
                    i = j
                    exist = True

            if exist and self.xyStack[i][2] != 0:
                self.onlyUserLabel[self.xyStack[i][0]][self.xyStack[i][1]].setText(str(self.xyStack[i][2]))
                self.answerboard[self.xyStack[i][0]][self.xyStack[i][1]] = self.xyStack[i][2]
            else:
                self.onlyUserLabel[y_][x_].clear()
                self.answerboard[y_][x_] = 0

            self.xyStack.pop()

    def checkFinish(self):
        if self.answerboard != base_board:
            QMessageBox.about(self, "Fail", "실패!")
            exit(0)
        else:
            QMessageBox.about(self, "Success", "성공!")
            exit(0)

    def closeEvent(self, event):
        reply = QMessageBox.question(self, 'Message', 'Are you sure to quit?',
                                     QMessageBox.Yes | QMessageBox.No, QMessageBox.No)

        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()


def clickable(widget):
    class Filter(QObject):
        clicked = pyqtSignal()  # pyside2 사용자는 pyqtSignal() -> Signal()로 변경

        def eventFilter(self, obj, event):
            if obj == widget:
                if event.type() == QEvent.MouseButtonRelease:
                    if obj.rect().contains(event.pos()):
                        self.clicked.emit()
                        return True
                        # The developer can opt for .emit(obj) to get the object within the slot.
            return False

    filter = Filter(widget)
    widget.installEventFilter(filter)
    return filter.clicked


# ----------------main-------------------
programstart = QApplication(sys.argv)
instance = StartWindow()
programstart.exec_()

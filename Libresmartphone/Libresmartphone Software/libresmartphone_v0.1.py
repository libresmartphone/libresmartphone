import sys
from PyQt4 import QtGui, QtCore
from PyQt4.QtCore import Qt
import serial
 
num = 0.0
newNum = 0.0
sumAll = 0.0
operator = ""
 
opVar = False
sumIt = 0

ser = serial.Serial('/dev/ttyACM0', 115200)
 
class Main(QtGui.QMainWindow):
 
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.initUI()
 
    def initUI(self):
 
        self.line = QtGui.QLineEdit(self)
        self.line.move(330,10)
        self.line.setReadOnly(True)
        self.line.setAlignment(Qt.AlignRight)
        self.line.resize(440,90)
 
        zero = QtGui.QPushButton("0",self)
        zero.move(110,310)
        zero.resize(90,90)
 
        one = QtGui.QPushButton("1",self)
        one.move(10,210)
        one.resize(90,90)
 
        two = QtGui.QPushButton("2",self)
        two.move(110,210)
        two.resize(90,90)
 
        three = QtGui.QPushButton("3",self)
        three.move(210,210)
        three.resize(90,90)
 
        four = QtGui.QPushButton("4",self)
        four.move(10,110)
        four.resize(90,90)
 
        five = QtGui.QPushButton("5",self)
        five.move(110,110)
        five.resize(90,90)
 
        six = QtGui.QPushButton("6",self)
        six.move(210,110)
        six.resize(90,90)
 
        seven = QtGui.QPushButton("7",self)
        seven.move(10,10)
        seven.resize(90,90)
 
        eight = QtGui.QPushButton("8",self)
        eight.move(110,10)
        eight.resize(90,90)
 
        nine = QtGui.QPushButton("9",self)
        nine.move(210,10)
        nine.resize(90,90)
 
        OK = QtGui.QPushButton("OK",self)
        OK.move(630,110)
        OK.resize(130,90)
        OK.clicked.connect(self.OK)

 
        hang = QtGui.QPushButton("",self)
        hang.move(480,110)
        hang.resize(130,90)
        hang.setIcon(QtGui.QIcon('hang.png'))
        hang.setIconSize(QtCore.QSize(134,113))
        hang.setStyleSheet("background-color:red;")
        hang.clicked.connect(self.hang) 
         
        unlock = QtGui.QPushButton("Unlock",self)
        unlock.move(440,310)
        unlock.resize(210,90)
        unlock.clicked.connect(self.unlock)
 
        call = QtGui.QPushButton("",self)
        call.move(330,110)
        call.resize(130,90)
        call.setIcon(QtGui.QIcon('call.png'))
        call.setIconSize(QtCore.QSize(90,90))
        call.clicked.connect(self.call)
        call.setStyleSheet("background-color:green;")
 
        clear = QtGui.QPushButton("Clear",self)
        clear.move(560,210)
        clear.resize(210,90)
        clear.clicked.connect(self.clear)
 
        delete = QtGui.QPushButton("Delete",self)
        delete.move(330,210)
        delete.resize(210,90)
        delete.clicked.connect(self.delete)
 
        nums = [zero,one,two,three,four,five,six,seven,eight,nine]
 
 
        for i in nums:
            i.setStyleSheet("color:blue;")
            i.clicked.connect(self.Nums)
 
        
             
#---------Window settings --------------------------------
         
        self.setGeometry(300,300,210,220)
        self.setFixedSize(795,400)
        self.setWindowTitle("")
        self.setWindowIcon(QtGui.QIcon(""))
        self.show()
        self.setStyleSheet('font-size: 50pt')
 
    def Nums(self):
        global num
        global newNum
        global opVar
         
        sender = self.sender()
         
        newNum = int(sender.text())
        setNum = str(newNum)
 
 
        if opVar == False:
            self.line.setText(self.line.text() + setNum)
 
 
        else:
            self.line.setText(setNum)
            opVar = False

        ser.write(setNum)
             
         
    def OK(self):

        ser.write('\n')
 
    def hang(self):

        ser.write('h')
        ser.write('\n')

    def fm(self):

        ser.write('f')
        ser.write('\n')

    def unlock(self):

        ser.write('U')
        ser.write('\n')

    def xfm(self):

        ser.write('F')
        ser.write('\n')
  
    def call(self):

        ser.write('c')

    def clear(self):

        ser.write('F')
        ser.write('\n')

    def delete(self):

        self.line.backspace()

        # el delete i el clear no funcionen perque es en IDLE i no es pot eliminar un cop escrit

 
 
def main():
    app = QtGui.QApplication(sys.argv)
    main= Main()
    main.show()
 
    sys.exit(app.exec_())
 
if __name__ == "__main__":
    main()

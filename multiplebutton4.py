import sys
from PyQt4 import QtCore, QtGui
import serial

ser = serial.Serial('/dev/ttyACM1', 115200)

class Class1(QtGui.QMainWindow):
    def __init__(self):
        super(Class1, self).__init__()
        self.func()

    def func(self):

        layout=QtGui.QHBoxLayout()  # layout for the central widget

        widget=QtGui.QWidget(self)  # central widget
        widget.setLayout(layout)


        number_group=QtGui.QButtonGroup(widget) # Number group
        self.button=QtGui.QPushButton('Call', self)
        number_group.addButton(self.button)
        self.button.clicked.connect(self.handleButton)
        b2=QtGui.QPushButton('Hang')
        number_group.addButton(b2)
        b3=QtGui.QPushButton('Home')
        number_group.addButton(b2)
        layout.addWidget(self.button)
        layout.addWidget(b2)
        layout.addWidget(b3)

        # assign the widget to the main window
        self.setCentralWidget(widget)
        self.show()

    def handleButton(self):
        ser.write('c')

   



def main():
    app = QtGui.QApplication(sys.argv)
    mw = Class1()
    mw.show()
    sys.exit(app.exec_())


if __name__=='__main__':
    main()

import sys
from PyQt4 import QtCore, QtGui
import serial

ser = serial.Serial('/dev/ttyACM0', 115200)

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

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
        b2=QtGui.QPushButton('Hang', self)
        number_group.addButton(b2)
        b2.clicked.connect(self.handleButton_2)
        b3=QtGui.QPushButton('Home', self)
        b3.clicked.connect(self.handleButton_3)
        number_group.addButton(b3)
        layout.addWidget(self.button)
        layout.addWidget(b2)
        layout.addWidget(b3)
        self.verticalLayout_2 = QtGui.QVBoxLayout(widget)
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.label = QtGui.QLabel(widget)
        self.label.setAlignment(QtCore.Qt.AlignBottom|QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft)
        self.label.setObjectName(_fromUtf8("label"))
        self.verticalLayout_2.addWidget(self.label)
        self.lineEdit = QtGui.QLineEdit(widget)
        self.lineEdit.setObjectName(_fromUtf8("lineEdit"))
        self.verticalLayout_2.addWidget(self.lineEdit)

        

        # assign the widget to the main window
        self.setCentralWidget(widget)
        self.show()

    def handleButton(self):
        ser.write('c')

    def handleButton_2(self):
        ser.write('h')
        
    def handleButton_3(self):
        ser.write('XXXXXXXX')
        ser.write('\n')

   


def main():
    app = QtGui.QApplication(sys.argv)
    mw = Class1()
    mw.show()
    sys.exit(app.exec_())


if __name__=='__main__':
    main()

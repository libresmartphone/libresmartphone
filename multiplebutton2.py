import sys
from PyQt4 import QtCore, QtGui

class Class1(QtGui.QMainWindow):
    def __init__(self):
        super(Class1, self).__init__()
        self.func()

    def func(self):

        layout=QtGui.QHBoxLayout()  # layout for the central widget

        widget=QtGui.QWidget(self)  # central widget
        widget.setLayout(layout)


        number_group=QtGui.QButtonGroup(widget) # Number group
        b1=QtGui.QPushButton('Call')
        number_group.addButton(b1)
        b2=QtGui.QPushButton('Hang')
        number_group.addButton(b2)
        b3=QtGui.QPushButton('Home')
        number_group.addButton(b2)
        layout.addWidget(b1)
        layout.addWidget(b2)
        layout.addWidget(b3)

        # assign the widget to the main window
        self.setCentralWidget(widget)
        self.show()




def main():
    app = QtGui.QApplication(sys.argv)
    mw = Class1()
    mw.show()
    sys.exit(app.exec_())


if __name__=='__main__':
    main()

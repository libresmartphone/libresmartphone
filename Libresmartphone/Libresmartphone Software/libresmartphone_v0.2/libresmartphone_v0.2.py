
from PyQt4 import QtGui, QtCore 
import sys, Queue, serial, threading, time, glob

##ser = serial.Serial('/dev/ttyACM0', 115200)

class finicial(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        self.BuscarSer()
        self.PTabLSP()

##class GuiLSP(QtGui.QMainWindow):
##
##    def __init__(self, queue, endcommand, *args):
##        QtGui.QMainWindow.__init__(self, *args)
##        self.queue = queue
##        self.endcommand = endcommand
####        self.PTabLSP()
##
##    def closeEvent(self,ev):
##        self.endcommand()
##
##    def processIncoming(self):
##        # Tracta tots els missatges actuals de la queue.
##        while self.queue.qsize():
##            try:
##                msg = self.queue.get(0)
##                #Podem comprovar els missatges i executar processos depenent
##                #del missatge, de moment nomes l'imprimim.
##                Tserial.insertPlainText(str(msg)) 
##                # Per anar a l'ultima linia del text (autoscroll)
##                Tserial.ensureCursorVisible()
##            except Queue.Empty:
##                pass
        
    def BuscarSer(self):

        global ser
        
        if sys.platform.startswith('linux'):
            lports_temp = glob.glob('/dev/ttyACM[0-9]')
        elif sys.platform.startswith('win'):
            lports_temp = ['COM' + str(i + 1) for i in range(256)]
        elif sys.platform.startswith('darwin'):
            lports_temp = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError ('Plataforma no soportada')
        result =[]
        for a_port in lports_temp:
            try:
                ser = serial.Serial(a_port, 115200)
                client = ThreadedClient()
##                ser.close()
                result.append(a_port)
            except serial.SerialException:
                pass
        print result

##        for a_port in lports_temp:
##            try:
##                ##        ser = serial.Serial('/dev/ttyACM0', 115200)
##                s = serial.Serial(a_port, 115200)
##                ## LLegeixo una linea perque quan s'enxufa surt'Initializing...
##                ## pero queda tot penjat si esta engegat
####                car = s.readline()
##                s.write('b')
##                s.write('\n')
##                car = s.readline()
##                print car
##                car = s.readline()
##                print car
##                if car[0:4] == 'Init':   
####                   s.write('b')
####                   s.write('\n')
##                   car = s.readline()
##                   print car
##                   car = s.readline()
##                   print car
##                   car = s.readline()
##                   print car
##                   car = s.readline()
##                   print car
##                if car[0:4] == 'VBat':
##                    ser = s
##                    print 'ja puc sortir del for'
##                    print 'Yupi, yupi, yupi..'
##                    print car
##                    print car[0:4]
##                    print ser
##                    client = ThreadedClient()
##                    break
##                else:
##                    print car
##                    print car[0:4]
##                    print 'merda amb un cordill'
##                s.close()
##                result.append(a_port)
##            except serial.SerialException:
##                pass
##        print result
        
    def PTabLSP(self):
        self.setGeometry(300,300,210,200)
        self.setFixedSize(795,400)
        self.setWindowTitle("LIBRESMARTPHONE")
        
        #Afegim el tab a la finestra principal i el fem de la mida de la finestra
        self._tabWidget = QtGui.QTabWidget(self)
        self._tabWidget.resize(795,400)
        tab1 = QtGui.QWidget()
        tab2 = QtGui.QWidget()
        tab3 = QtGui.QWidget()
##        self._tabWidget.addTab(tab1, "Phone")
##        self._tabWidget.addTab(tab2, "SMS")
##        self._tabWidget.addTab(tab3, "Config")
        self._tabWidget.setIconSize(QtCore.QSize(110,60))
        self._tabWidget.addTab(tab1, QtGui.QIcon('call.png'), "")
        self._tabWidget.addTab(tab2, QtGui.QIcon('message.png'),"")
        self._tabWidget.addTab(tab3, QtGui.QIcon('gear.png'), "")
        self._tabWidget.setTabPosition(QtGui.QTabWidget.East)   

        #-----------------------------------------------
        #    Disseny tab-Phone --> tab1
        #-----------------------------------------------
        vcol1 = [0,1,4,7]
        vcol2 = [2,5,8]
        vcol3 = [3,6,9]
        for numdig in range(0,10):
            NomBoto = str(numdig)
##            print(NomBoto)
            NomBoto = QtGui.QPushButton(str(numdig),self._tabWidget.widget(0))
            NomBoto.setStyleSheet('font-size: 50pt')          
            NomBoto.resize(90,90)
            if numdig in vcol1:
                x = 10
            elif numdig in vcol2:
                x = 110
            elif numdig in vcol3:
                x = 210
            if numdig == 0:
                y = 305
            elif numdig in range(1,8,3):
                y = y - 100
            NomBoto.move(x,y)
            NomBoto.clicked.connect(self.Numeros)

        Bunlock = QtGui.QPushButton("Unlock",self._tabWidget.widget(0))
        Bunlock.resize(190,90)
        Bunlock.move(110,305)
        Bunlock.setStyleSheet('font-size: 40pt')
        Bunlock.clicked.connect(self.Unlock)

        global Lnumph
        Lnumph = QtGui.QLineEdit(self._tabWidget.widget(0))
        Lnumph.resize(400,90)
        Lnumph.move(310,5)
        Lnumph.setReadOnly(True)
        Lnumph.setAlignment(QtCore.Qt.AlignRight)
        Lnumph.setStyleSheet('font-size: 50pt')

        global Tserial
        Tserial = QtGui.QTextEdit(self._tabWidget.widget(0))
        Tserial.resize(400,90)
        Tserial.move(310,305)
        Tserial.setReadOnly(True)
        Tserial.setFontPointSize(12)

        Bcall = QtGui.QPushButton("",self._tabWidget.widget(0))
        Bcall.resize(130,90)
        Bcall.move(310,105)
        Bcall.setIcon(QtGui.QIcon('call.png'))
        Bcall.setIconSize(QtCore.QSize(90,90))
        Bcall.setStyleSheet("background-color:green;")
        Bcall.clicked.connect(self.Call)
        
        Bhang = QtGui.QPushButton("",self._tabWidget.widget(0))
        Bhang.resize(130,90)
        Bhang.move(450,105)
        Bhang.setIcon(QtGui.QIcon('hang.png'))
        Bhang.setIconSize(QtCore.QSize(140,100))
        Bhang.setStyleSheet("background-color:red;")
        Bhang.clicked.connect(self.Hang)

        Bok = QtGui.QPushButton("OK",self._tabWidget.widget(0))
        Bok.resize(120,90)
        Bok.move(590,105)
        Bok.setStyleSheet('font-size: 40pt')
        Bok.clicked.connect(self.OK)

        Bdelete = QtGui.QPushButton("Delete",self._tabWidget.widget(0))
        Bdelete.resize(190,90)
        Bdelete.move(310,205)
        Bdelete.setStyleSheet('font-size: 40pt')
        Bdelete.clicked.connect(self.Delete)

        Bclear = QtGui.QPushButton("Clear",self._tabWidget.widget(0))
        Bclear.resize(190,90)
        Bclear.move(520,205)
        Bclear.setStyleSheet('font-size: 40pt')
        Bclear.clicked.connect(self.Clear)

        #-----------------------------------------------
        #    Disseny tab-Config --> tab3
        #-----------------------------------------------
        BLports = QtGui.QPushButton("Ports",self._tabWidget.widget(2))
        BLports.resize(190,90)
        BLports.move(110,205)
        BLports.setStyleSheet('font-size: 40pt')
##3        BLports.clicked.connect(self.LlistaPorts)
        BLports.clicked.connect(self.BuscarSer)
        
##
##    def output(self):
##        ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
        
    def Numeros(self):
        sender = self.sender()
        Lnumph.setText(Lnumph.text() + sender.text())

    def Unlock(self):
        ser.write('U')
        ser.write('\n')

    def Call(self):
        ser.write('c')
        ser.write(str(Lnumph.text()))
        ser.write('\n')

    def Hang(self):
        ser.write('h')
        ser.write('\n')

    def OK(self):
        ser.write(str(Lnumph.text()))
        Lnumph.clear()

    def Delete(self):
        Lnumph.backspace()

    def Clear(self):
        Lnumph.clear()

    def Fm(self):
        ser.write('f')
        ser.write('\n')

    def Xfm(self):
        ser.write('F')
        ser.write('\n')
        
    def LlistaPorts(self):
        if sys.platform.startswith('linux'):
            lports_temp = glob.glob('/dev/ttyACM[0-9]')
        elif sys.platform.startswith('win'):
            lports_temp = ['COM' + str(i + 1) for i in range(256)]
        elif sys.platform.startswith('darwin'):
            lports_temp = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError ('Plataforma no soportada')
        result =[]
        for a_port in lports_temp:
            try:
                s = serial.Serial(a_port, 115200)
                s.write('b')
                s.write('\n')
                car = s.readline()
                car = s.readline()
                if car[0:4] == 'VBat':
##                car = s.readline()
##                if car[0-3] == '%':
##                    print 'YUPI, he trobat un % casualitat total'
                    print 'Yupi, yupi, yupi..'
                    print car
                    print car[0:4]
                else:
                    print car
                    print car[0-3]
                    print 'merda amb un cordill'
                s.close()
                result.append(a_port)
            except serial.SerialException:
                pass
        print result

##1class GuiLSP(QtGui.QMainWindow):
class GuiLSP():

    def __init__(self, queue, endcommand, *args):
##1        QtGui.QMainWindow.__init__(self, *args)
        self.queue = queue
        self.endcommand = endcommand
##        self.PTabLSP()

    def closeEvent(self,ev):
        self.endcommand()

    def processIncoming(self):
        # Tracta tots els missatges actuals de la queue.
        while self.queue.qsize():
            try:
                msg = self.queue.get(0)
                #Podem comprovar els missatges i executar processos depenent
                #del missatge, de moment nomes l'imprimim.
                Tserial.insertPlainText(str(msg)) 
                # Per anar a l'ultima linia del text (autoscroll)
                Tserial.ensureCursorVisible()
            except Queue.Empty:
                pass
        
class ThreadedClient:
    """
    Launch the main part of the GUI and the worker thread. periodicCall and
    endApplication could reside in the GUI part, but putting them here
    means that you have all the thread controls in a single place.
    """
    def __init__(self):
        # Create the queue
        self.queue = Queue.Queue()

        # Set up the GUI part
        self.gui=GuiLSP(self.queue, self.endApplication)
##1        self.gui.show()

        # A timer to periodically call periodicCall :-)
        self.timer = QtCore.QTimer()
        QtCore.QObject.connect(self.timer,
                           QtCore.SIGNAL("timeout()"),
                           self.periodicCall)
        # Start the timer -- this replaces the initial call to periodicCall
        self.timer.start(100)

        # Set up the thread to do asynchronous I/O
        # More can be made if necessary
        self.running = 1
        self.thread1 = threading.Thread(target=self.workerThread1)
        self.thread1.start()

##    def IniciaThread(self):
##        # Set up the thread to do asynchronous I/O
##        # More can be made if necessary
##        self.running = 1
##        self.thread1 = threading.Thread(target=self.workerThread1)
##        self.thread1.start()
        
    def periodicCall(self):
        """
        Check every 100 ms if there is something new in the queue.
        """
        self.gui.processIncoming()
        if not self.running:
            root.quit()

    def endApplication(self):
        self.running = 0

    def workerThread1(self):
        """
        This is where we handle the asynchronous I/O. 
        Put your stuff here.
        """
        while self.running:

            #la seguent definicio es necesaria, ja que sino nomes escriu un cop
##2            ser = serial.Serial('/dev/ttyACM0', 115200)
            msg = ser.readline();
            if (msg):
                self.queue.put(msg)
            else: pass
            #si descomento la seguent linia em dona el seguent error:
            #Attempting to use a port that is not open
##2            ser.close()


root = QtGui.QApplication(sys.argv)
##client = ThreadedClient()
pmovil = finicial()
pmovil.show()
sys.exit(root.exec_())
            
            

##
##def main():
##app = QtGui.QApplication(sys.argv)
##
##tabs = QtGui.QTabWidget()
##tab1 = QtGui.QWidget()
##tab2 = QtGui.QWidget()
##tab3 = QtGui.QWidget()
##
###Redimensionem
##tabs.resize(800,400)
##tabs.setWindowTitle('LIBRESMARTPHONE')
##
###Per mostrar els tabs en el lateral dret
##tabs.setTabPosition(QtGui.QTabWidget.East)
##tabs.addTab(tab1, "Phone")
##tabs.addTab(tab2, "SMS")
##tabs.addTab(tab3, "Config")
##tabs.show()
##
###Disseny tab-Phone    
##
##zero = QtGui.QPushButton("0")
##one = QtGui.QPushButton("1")
##two = QtGui.QPushButton("2")
##three = QtGui.QPushButton("3")
##four = QtGui.QPushButton("4")
##five = QtGui.QPushButton("5")
##six = QtGui.QPushButton("6")
##seven = QtGui.QPushButton("7")
##eight = QtGui.QPushButton("8")  
##nine = QtGui.QPushButton("9")
##
##
##
####
####    Gridlayout1 = QtGui.QGridLayout()
####    Gridlayout1.addWidget(seven,1,1)
####    Gridlayout1.addWidget(eight,1,2)
####    Gridlayout1.addWidget(nine,1,3)
####    Gridlayout1.addWidget(four,2,1)
####    Gridlayout1.addWidget(five,2,2)
####    Gridlayout1.addWidget(six,2,3)
####    Gridlayout1.addWidget(one,3,1)
####    Gridlayout1.addWidget(two,3,2)
####    Gridlayout1.addWidget(three,3,3)
####    Gridlayout1.addWidget(zero,4,1)
####    tab1.setLayout(Gridlayout1)
####    LNPhone =  QtGui.QLineEdit()
####    LNPhone.move(330,10)
##
###Set Layout pel primer tab
####    tab1.setLayout(vBoxlayout1)
##
###Fi Disseny tab-Phone
###-------------------------------------------------------
##
###Disseny tab3 
##vBoxlayout3 = QtGui.QVBoxLayout()
##BConnect = QtGui.QPushButton("Connect")
##BNohose = QtGui.QPushButton("Encara no se la funcio")
##vBoxlayout3.addWidget(BConnect)
##vBoxlayout3.addWidget(BNohose)
###Set Layout pel tercer tab
##tab3.setLayout(vBoxlayout3)
###Fi Disseny tab3
###-------------------------------------------------------
##
##sys.exit(app.exec_())
##
##
##
##if __name__ == '__main__':
##main()
##
##    tabs = QtGui.QTabWidget()
##    BConnect = QtGui.QPushButton("Connect")
##    BNohose = QtGui.QPushButton("Encara no se la funcio")
##
##    tab1 = QtGui.QWidget()
##    tab2 = QtGui.QWidget()
##    tab3 = QtGui.QWidget()
##
##    vBoxlayout = QtGui.QVBoxLayout()
##    vBoxlayout.addWidget (BConnect)  
##    vBoxlayout.addWidget (BNohose)
##
##    #Redimensionem
##    tabs.resize(800,400)
##    
##    #Set Layout pel tercer tab
##    tab3.setLayout(vBoxlayout)
##
##    tabs.addTab(tab1, "Phone")
##    tabs.addTab(tab2, "SMS")
##    tabs.addTab(tab3, "Config")
##
##    tabs.setWindowTitle('LIBRESMARTPHONE')
##    #Pels tabs en el lateral dret
##    tabs.setTabPosition(QtGui.QTabWidget.East)
##    tabs.show()
##
##    sys.exit(app.exec_())
##
##if __name__ == '__main__':
##    main()

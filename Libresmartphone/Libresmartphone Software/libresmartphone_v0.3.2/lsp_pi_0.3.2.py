## -*- coding: utf-8 -*-
##This code is realized by GACICVTAC

from PyQt4 import QtGui, QtCore 
import sys, Queue, serial, threading, time, glob


class finicial(QtGui.QMainWindow):
    def __init__(self):
        
        global emtruquen, teditdisp, AonEscric, TipLLet
        emtruquen = 'N'
        teditdisp = 0
        AonEscric = ''
        TipLLet = 'min'

        QtGui.QMainWindow.__init__(self)
        self.BuscarSer()
        self.PTabLSP()
       
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
                result.append(a_port)
            except serial.SerialException:
                pass
        print result

    def PTabLSP(self):

##        self.setGeometry(300,300,210,200)
        self.setFixedSize(795,400)
        self.setWindowTitle("LIBRESMARTPHONE")
        
        #Afegim el tab a la finestra principal i el fem de la mida de la finestra
        self._tabWidget = QtGui.QTabWidget(self)
        self._tabWidget.resize(795,400)
        tab1 = QtGui.QWidget()
        tab2 = QtGui.QWidget()
        tab3 = QtGui.QWidget()
        self._tabWidget.setIconSize(QtCore.QSize(110,60))
        self._tabWidget.addTab(tab1, QtGui.QIcon('call.png'), "")
        self._tabWidget.addTab(tab2, QtGui.QIcon('message.png'),"")
        self._tabWidget.addTab(tab3, QtGui.QIcon('gear.png'), "")
        self._tabWidget.setTabPosition(QtGui.QTabWidget.East)
        self._tabWidget.currentChanged.connect(self.CanviTab)

        #-----------------------------------------------
        #    Disseny tab-Phone --> tab1
        #-----------------------------------------------
        vcol1 = [0,1,4,7]
        vcol2 = [2,5,8]
        vcol3 = [3,6,9]
        for numdig in range(0,10):
            NomBoto = str(numdig)
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
        #    Disseny tab-SMS --> tab2
        #-----------------------------------------------
        TabSMS = QtGui.QTabWidget(self._tabWidget.widget(1))
        TabSMS.setFixedSize(710,400)
        trSMS = QtGui.QWidget()
        tsSMS = QtGui.QWidget()
        TabSMS.setIconSize(QtCore.QSize(100,40))
        TabSMS.addTab(tsSMS,QtGui.QIcon('messagesent.png'), "New SMS")
        TabSMS.addTab(trSMS,QtGui.QIcon('message.png'), "Read SMS")
        TabSMS.currentChanged.connect(self.CanviTabSMS)
        
        Lpn = QtGui.QLabel("Phone Number ", TabSMS.widget(0))
        Lpn.resize(90,30)
        Lpn.move(10,10)
        Lpn.setStyleSheet('font-size:10pt')

        global Tphn
        Tphn = MeuTextEdit(TabSMS.widget(0))
        Tphn.resize (390,40)
        Tphn.move(110,5)
        Tphn.setStyleSheet('font-size:30pt')
        Tphn.focusIn.connect(self.EscriuTphn)
        
        BSendMsg = QtGui.QPushButton("Send SMS",TabSMS.widget(0))
        BSendMsg.resize(190,40)
        BSendMsg.move(510,5)
        BSendMsg.setStyleSheet('font-size:30pt; background-color: orange')
        BSendMsg.clicked.connect(self.SendMsg)
        
        Ltm = QtGui.QLabel("Text Message ", TabSMS.widget(0))
        Ltm.resize(90,30)
        Ltm.move(10,50)
        Ltm.setStyleSheet('font-size:10pt')

        global TNewSms
        TNewSms = MeuTextEdit(TabSMS.widget(0))
        TNewSms.resize(600,100)
        TNewSms.move(110,45)
        TNewSms.setStyleSheet('font-size:25pt')
        TNewSms.focusIn.connect(self.EscriuTsms)

        GLteclat = QtGui.QGridLayout()
        Tecles = [
            ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'],
            ['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'],
            ['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', "'"],
            ['^','z', 'x', 'c', 'v', 'b', 'n', 'm', 'CLR', ' '],
            ['@', '(', '%', '*', '/', '-', '+', ',', '.', '?'],
         ]

        teclat= QtGui.QWidget(TabSMS.widget(0))
        teclat.setLayout(GLteclat)
        teclat.resize(700,210)
        teclat.move(5,140)
        
        for idxLin,Lin in enumerate(Tecles):
            for idxTec, Tecla in enumerate(Lin):
                NomBoto = Tecles[idxLin][idxTec]
                Tecla = QtGui.QPushButton(NomBoto)
                Tecla.setStyleSheet('font-size: 20pt; background-color: #FFEBCD')
                GLteclat.addWidget(Tecla,idxLin, idxTec)
                if idxLin == 0:
                    Tecla.clicked.connect(self.NumTV)
                else:              
                    Tecla.clicked.connect(self.LLetraTV)
                GLteclat.setColumnMinimumWidth(idxTec,10)
            GLteclat.setRowMinimumHeight(idxLin, 10)

        global Tmissatges
        Tmissatges = QtGui.QTextEdit(TabSMS.widget(1))
        Tmissatges.resize(704,345)
        Tmissatges.move(0,5)
        Tmissatges.setReadOnly(True)
        Tmissatges.setFontPointSize(12)

        #-----------------------------------------------
        #    Disseny tab-Config --> tab3
        #-----------------------------------------------
        
        BLports = QtGui.QPushButton("Ports",self._tabWidget.widget(2))
        BLports.resize(190,90)
        BLports.move(50,125)
        BLports.setStyleSheet('font-size: 40pt')
        BLports.clicked.connect(self.BuscarSer)


        global BN1, BN2, BN3, BN4, BN5
        GBnivbat = QtGui.QGroupBox('Battery',self._tabWidget.widget(2))
        GBnivbat.resize(100,395)
        GBnivbat.move(650,5)
        BN1 = QtGui.QPushButton(self._tabWidget.widget(2))
        BN1.resize(60,70)
        BN1.move(650,35)
        BN2 = QtGui.QPushButton(self._tabWidget.widget(2))
        BN2.resize(60,70)
        BN2.move(650,105)
        BN3 = QtGui.QPushButton(self._tabWidget.widget(2))
        BN3.resize(60,70)
        BN3.move(650,175)
        BN4 = QtGui.QPushButton(self._tabWidget.widget(2))
        BN4.resize(60,70)
        BN4.move(650,245)
        BN5 = QtGui.QPushButton(self._tabWidget.widget(2))
        BN5.resize(60,70)
        BN5.move(650,315)

    
    def CanviTab(self,indextab):    
        global teditdisp
        if indextab == 0:
            teditdisp = 0
        elif indextab == 1:
##            ser.write('R')
##            ser.write('\n')
##            Tmissatges.clear()
            teditdisp = 1
        elif indextab == 2:
             teditdisp = 0
             ser.write('b')
             ser.write('\n')

    def CanviTabSMS(self,indextabS):
        if indextabS == 1:     
            ser.write('R')
            ser.write('\n')
            Tmissatges.clear()
        
        
    def Numeros(self):
        sender = self.sender()
        Lnumph.setText(Lnumph.text() + sender.text())

    def Unlock(self):
        ser.write('U')
        ser.write('\n')

    def Call(self):
        if emtruquen == 'S':
           ser.write('p')
           ser.write('\n')
        else:
           ser.write('c')
           ser.write(str(Lnumph.text()))
           ser.write('\n')

    def Hang(self):
        ser.write('h')
        ser.write('\n')
        emtruquen = 'N'

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

    def SendMsg(self):
        ser.write('s')
        ser.write('\n')
        Numtelf = Tphn.toPlainText()
        ser.write(str(Numtelf))
        ser.write('\n')
        Newmiss = TNewSms.toPlainText()
        ser.write(str(Newmiss))
        ser.write('\n')

    def EscriuTphn(self):
        global AonEscric
        AonEscric = 'NTel'

    def EscriuTsms(self):
        global AonEscric
        AonEscric = 'NSms'

    def NumTV(self):
        global AonEscric
        
        NouCar = self.sender()
        if AonEscric == 'NTel':
            Tphn.insertPlainText(NouCar.text())
        else:
            if AonEscric == 'NSms':
               TNewSms.insertPlainText(NouCar.text())
               
    def LLetraTV(self):
        global AonEscric, TipLLet
        
        NouCar = self.sender()
        if NouCar.text() == '^':
            if TipLLet == 'min':
                TipLLet = 'maj'
            else:
                TipLLet = 'min'
        else:
            Caracter = NouCar.text()
            if TipLLet == 'maj':
               Caracter = Caracter.toUpper()
            if AonEscric == 'NSms':
                TNewSms.insertPlainText(Caracter) 
                if NouCar.text() == 'CLR':
                    TNewSms.clear()
            else:
                if AonEscric == 'NTel': 
                   if NouCar.text()== '+':
                      Tphn.insertPlainText(NouCar.text())
                   elif NouCar.text() == 'CLR':
                        Tphn.clear()
        
    def NivellBat(self, carrega_bat):
        if carrega_bat >= 80:
           BN5.setStyleSheet('background-color: blue')
           BN4.setStyleSheet('background-color: blue')
           BN3.setStyleSheet('background-color: blue')
           BN2.setStyleSheet('background-color: blue')
           BN1.setStyleSheet('background-color: blue')
        elif carrega_bat >= 60:
             BN5.setText("")
             BN5.setStyleSheet('background-color: blue')
             BN4.setStyleSheet('background-color: blue')
             BN3.setStyleSheet('background-color: blue')
             BN2.setStyleSheet('background-color: blue')
             BN1.setStyleSheet('background-color: window')
        elif carrega_bat >= 40:
             BN5.setText("")
             BN5.setStyleSheet('background-color: blue')
             BN4.setStyleSheet('background-color: blue')
             BN3.setStyleSheet('background-color: blue')
             BN2.setStyleSheet('background-color: window')
             BN1.setStyleSheet('background-color: window')
        elif carrega_bat >= 20:
             BN5.setText("")
             BN5.setStyleSheet('background-color: blue')
             BN4.setStyleSheet('background-color: blue')
             BN3.setStyleSheet('background-color: window')
             BN2.setStyleSheet('background-color: window')
             BN1.setStyleSheet('background-color: window')
        elif carrega_bat >= 5:
             BN5.setText("")
             BN5.setStyleSheet('background-color: blue')
             BN4.setStyleSheet('background-color: window')
             BN3.setStyleSheet('background-color: window')
             BN2.setStyleSheet('background-color: window')
             BN1.setStyleSheet('background-color: window')
        else :
             BN5.setText("X")
             BN5.setStyleSheet('font-size: 62pt; color: red')
             BN4.setStyleSheet('background-color: window')
             BN3.setStyleSheet('background-color: window')
             BN2.setStyleSheet('background-color: window')
             BN1.setStyleSheet('background-color: window')
                        
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
                    print car
                    print car[0:4]
                else:
                    print car
                    print car[0-3]
                s.close()
                result.append(a_port)
            except serial.SerialException:
                pass
        print result
        
class MeuTextEdit(QtGui.QTextEdit):

    focus_in = QtCore.pyqtSignal(name='focusIn')

    def focusInEvent(self, event):
        self.focus_in.emit()
        QtGui.QTextEdit.focusInEvent(self,event)
                             
class GuiLSP():

    def __init__(self, queue, endcommand, *args):
        self.queue = queue
        self.endcommand = endcommand

    def closeEvent(self,ev):
        self.endcommand()

    def processIncoming(self):
        global teditdisp
        global emtruquen
        
        # Tracta tots els missatges actuals de la queue.        
        while self.queue.qsize():
            try:
                msg = self.queue.get(0)
                #Podem comprovar els missatges i executar processos depenent
                #del missatge, de moment nomes l'imprimim.
                if teditdisp == 0:
                   Tserial.insertPlainText(str(msg))
                # Per anar a l'ultima linia del text (autoscroll)
                   Tserial.ensureCursorVisible()
                elif teditdisp == 1:
                     Tmissatges.insertPlainText(str(msg))
                     Tmissatges.ensureCursorVisible()
                if msg[0:4]=='RING':
                   emtruquen = 'S'
                elif msg[0:10]=='NO CARRIER'or msg[0:2]== 'OK':
                     emtruquen = 'N'
                elif msg[0:4]=='VPct':
                     niv_car_bat = int(msg[7:9])
                     pmovil.NivellBat(niv_car_bat)
                     
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
            msg = ser.readline();
            if (msg):
                self.queue.put(msg)
            else: pass



root = QtGui.QApplication(sys.argv)
pmovil = finicial()
pmovil.show()
sys.exit(root.exec_())
            

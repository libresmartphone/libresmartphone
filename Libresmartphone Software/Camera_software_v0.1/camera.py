from PyQt4 import QtGui, QtCore
import sys, picamera

class Camera (QtGui.QWidget):
      def __init__(self):
          super(Camera,self).__init__()

          self.initUI()

      def initUI(self):
          
          self.setFixedSize(795,400)
          self.setWindowTitle('LibreSmartPhone Camera')
              
          BFoto = QtGui.QPushButton(QtGui.QIcon('camerafotos.png'),"")
          BFoto.setIconSize(QtCore.QSize(90,90))
          BFoto.clicked.connect(self.FerFoto)
          BVideo = QtGui.QPushButton(QtGui.QIcon('video.png'),"")
          BVideo.setIconSize(QtCore.QSize(90,90))
          BVideo.clicked.connect(self.FerVideo)

               
          hbox = QtGui.QHBoxLayout()
          hbox.addStretch(1)
          hbox.addWidget(BFoto)
          hbox.addWidget(BVideo)

          vbox = QtGui.QVBoxLayout()
          vbox.addStretch(1)
          vbox.addLayout(hbox)

          self.setLayout(vbox)        
          
          self.show()

          global camera
          camera = picamera.PiCamera()

      def FerFoto(self):
##        captura imatge:
          global camera
          camera.capture('image.jpg')
          
      def FerVideo(self):
##        captura video
          global camera
          camera.start_recording('video.h264')
          sleep(5)
          camera.stop_recording()

def main():
    app = QtGui.QApplication(sys.argv)
    clsp = Camera()
    sys.exit(app.exec_())
 
if __name__ == "__main__":
    main()
                              

# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'MainForm.ui'
##
## Created by: Qt User Interface Compiler version 6.7.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QFrame, QGridLayout, QHBoxLayout,
    QLabel, QMainWindow, QProgressBar, QPushButton,
    QRadioButton, QSizePolicy, QTabWidget, QVBoxLayout,
    QWidget)
import Image_rc

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.setEnabled(True)
        MainWindow.resize(1024, 600)
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        MainWindow.setMinimumSize(QSize(0, 0))
        MainWindow.setMaximumSize(QSize(1920, 1080))
        font = QFont()
        font.setFamilies([u"Arial"])
        font.setPointSize(14)
        font.setBold(True)
        MainWindow.setFont(font)
        MainWindow.setCursor(QCursor(Qt.CursorShape.ArrowCursor))
        MainWindow.setTabletTracking(True)
        MainWindow.setLayoutDirection(Qt.LeftToRight)
        MainWindow.setAutoFillBackground(False)
        MainWindow.setStyleSheet(u"")
        MainWindow.setIconSize(QSize(30, 30))
        MainWindow.setToolButtonStyle(Qt.ToolButtonIconOnly)
        MainWindow.setAnimated(False)
        MainWindow.setTabShape(QTabWidget.Rounded)
        MainWindow.setDockOptions(QMainWindow.AllowTabbedDocks)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.horizontalLayout_2 = QHBoxLayout(self.centralwidget)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.tabWidget_Main = QTabWidget(self.centralwidget)
        self.tabWidget_Main.setObjectName(u"tabWidget_Main")
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Preferred)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.tabWidget_Main.sizePolicy().hasHeightForWidth())
        self.tabWidget_Main.setSizePolicy(sizePolicy1)
        font1 = QFont()
        font1.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font1.setPointSize(16)
        font1.setBold(True)
        self.tabWidget_Main.setFont(font1)
        self.tabWidget_Main.setTabShape(QTabWidget.Rounded)
        self.tab_Run = QWidget()
        self.tab_Run.setObjectName(u"tab_Run")
        self.horizontalFrame_2 = QFrame(self.tab_Run)
        self.horizontalFrame_2.setObjectName(u"horizontalFrame_2")
        self.horizontalFrame_2.setGeometry(QRect(0, 0, 1001, 541))
        self.gridLayout_6 = QGridLayout(self.horizontalFrame_2)
        self.gridLayout_6.setObjectName(u"gridLayout_6")
        self.verticalLayout_Weight = QVBoxLayout()
        self.verticalLayout_Weight.setObjectName(u"verticalLayout_Weight")
        self.verticalLayout_Weight.setContentsMargins(-1, -1, -1, 0)
        self.gridFrame_W1 = QFrame(self.horizontalFrame_2)
        self.gridFrame_W1.setObjectName(u"gridFrame_W1")
        self.gridFrame_W1.setFrameShape(QFrame.Panel)
        self.gridLayout_2 = QGridLayout(self.gridFrame_W1)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.progressBar = QProgressBar(self.gridFrame_W1)
        self.progressBar.setObjectName(u"progressBar")
        self.progressBar.setValue(24)

        self.gridLayout_2.addWidget(self.progressBar, 1, 0, 1, 3)

        self.label = QLabel(self.gridFrame_W1)
        self.label.setObjectName(u"label")

        self.gridLayout_2.addWidget(self.label, 0, 0, 1, 1)

        self.label_3 = QLabel(self.gridFrame_W1)
        self.label_3.setObjectName(u"label_3")

        self.gridLayout_2.addWidget(self.label_3, 0, 2, 1, 1)

        self.label_2 = QLabel(self.gridFrame_W1)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout_2.addWidget(self.label_2, 0, 1, 1, 1)


        self.verticalLayout_Weight.addWidget(self.gridFrame_W1)

        self.gridFrame_W2 = QFrame(self.horizontalFrame_2)
        self.gridFrame_W2.setObjectName(u"gridFrame_W2")
        self.gridFrame_W2.setFrameShape(QFrame.Panel)
        self.gridLayout_3 = QGridLayout(self.gridFrame_W2)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.label_4 = QLabel(self.gridFrame_W2)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout_3.addWidget(self.label_4, 0, 1, 1, 1)

        self.label_5 = QLabel(self.gridFrame_W2)
        self.label_5.setObjectName(u"label_5")

        self.gridLayout_3.addWidget(self.label_5, 0, 0, 1, 1)

        self.label_6 = QLabel(self.gridFrame_W2)
        self.label_6.setObjectName(u"label_6")

        self.gridLayout_3.addWidget(self.label_6, 0, 2, 1, 1)

        self.progressBar_2 = QProgressBar(self.gridFrame_W2)
        self.progressBar_2.setObjectName(u"progressBar_2")
        self.progressBar_2.setValue(24)

        self.gridLayout_3.addWidget(self.progressBar_2, 1, 0, 1, 3)


        self.verticalLayout_Weight.addWidget(self.gridFrame_W2)

        self.gridFrame_W3 = QFrame(self.horizontalFrame_2)
        self.gridFrame_W3.setObjectName(u"gridFrame_W3")
        self.gridFrame_W3.setFrameShape(QFrame.Panel)
        self.gridLayout_4 = QGridLayout(self.gridFrame_W3)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.label_7 = QLabel(self.gridFrame_W3)
        self.label_7.setObjectName(u"label_7")

        self.gridLayout_4.addWidget(self.label_7, 0, 1, 1, 1)

        self.label_8 = QLabel(self.gridFrame_W3)
        self.label_8.setObjectName(u"label_8")

        self.gridLayout_4.addWidget(self.label_8, 0, 0, 1, 1)

        self.label_9 = QLabel(self.gridFrame_W3)
        self.label_9.setObjectName(u"label_9")

        self.gridLayout_4.addWidget(self.label_9, 0, 2, 1, 1)

        self.progressBar_3 = QProgressBar(self.gridFrame_W3)
        self.progressBar_3.setObjectName(u"progressBar_3")
        self.progressBar_3.setValue(24)

        self.gridLayout_4.addWidget(self.progressBar_3, 1, 0, 1, 3)


        self.verticalLayout_Weight.addWidget(self.gridFrame_W3)

        self.gridFrame_W4 = QFrame(self.horizontalFrame_2)
        self.gridFrame_W4.setObjectName(u"gridFrame_W4")
        self.gridFrame_W4.setFrameShape(QFrame.Panel)
        self.gridLayout_5 = QGridLayout(self.gridFrame_W4)
        self.gridLayout_5.setObjectName(u"gridLayout_5")
        self.label_10 = QLabel(self.gridFrame_W4)
        self.label_10.setObjectName(u"label_10")

        self.gridLayout_5.addWidget(self.label_10, 0, 1, 1, 1)

        self.label_11 = QLabel(self.gridFrame_W4)
        self.label_11.setObjectName(u"label_11")

        self.gridLayout_5.addWidget(self.label_11, 0, 0, 1, 1)

        self.label_12 = QLabel(self.gridFrame_W4)
        self.label_12.setObjectName(u"label_12")

        self.gridLayout_5.addWidget(self.label_12, 0, 2, 1, 1)

        self.progressBar_4 = QProgressBar(self.gridFrame_W4)
        self.progressBar_4.setObjectName(u"progressBar_4")
        self.progressBar_4.setValue(24)

        self.gridLayout_5.addWidget(self.progressBar_4, 1, 0, 1, 3)


        self.verticalLayout_Weight.addWidget(self.gridFrame_W4)


        self.gridLayout_6.addLayout(self.verticalLayout_Weight, 0, 1, 1, 1)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setSpacing(4)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(-1, -1, -1, 0)
        self.horizontalFrameDirection = QFrame(self.horizontalFrame_2)
        self.horizontalFrameDirection.setObjectName(u"horizontalFrameDirection")
        self.horizontalFrameDirection.setFrameShape(QFrame.Panel)
        self.horizontalFrameDirection.setLineWidth(1)
        self.horizontalLayout = QHBoxLayout(self.horizontalFrameDirection)
        self.horizontalLayout.setSpacing(2)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.pushButton_Up = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Up.setObjectName(u"pushButton_Up")
        icon = QIcon()
        icon.addFile(u":/Medical/Picture/up arrow.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Up.setIcon(icon)
        self.pushButton_Up.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Up)

        self.pushButton_Down = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Down.setObjectName(u"pushButton_Down")
        icon1 = QIcon()
        icon1.addFile(u":/Medical/Picture/down arrow.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Down.setIcon(icon1)
        self.pushButton_Down.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Down)

        self.pushButton_Front = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Front.setObjectName(u"pushButton_Front")
        self.pushButton_Front.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon2 = QIcon()
        icon2.addFile(u":/Medical/Picture/Arrow Leftt45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Front.setIcon(icon2)
        self.pushButton_Front.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Front)

        self.pushButton_Rear = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Rear.setObjectName(u"pushButton_Rear")
        self.pushButton_Rear.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon3 = QIcon()
        icon3.addFile(u":/Medical/Picture/Arrow Right45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Rear.setIcon(icon3)
        self.pushButton_Rear.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Rear)

        self.pushButton_Power = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Power.setObjectName(u"pushButton_Power")
        sizePolicy.setHeightForWidth(self.pushButton_Power.sizePolicy().hasHeightForWidth())
        self.pushButton_Power.setSizePolicy(sizePolicy)
        font2 = QFont()
        font2.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font2.setPointSize(30)
        font2.setBold(True)
        self.pushButton_Power.setFont(font2)
        self.pushButton_Power.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Power)

        self.horizontalLayout.setStretch(0, 1)
        self.horizontalLayout.setStretch(1, 1)
        self.horizontalLayout.setStretch(2, 1)
        self.horizontalLayout.setStretch(3, 1)
        self.horizontalLayout.setStretch(4, 1)

        self.verticalLayout.addWidget(self.horizontalFrameDirection)

        self.horizontalFrame0 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame0.setObjectName(u"horizontalFrame0")
        sizePolicy.setHeightForWidth(self.horizontalFrame0.sizePolicy().hasHeightForWidth())
        self.horizontalFrame0.setSizePolicy(sizePolicy)
        self.horizontalFrame0.setFrameShape(QFrame.Panel)
        self.horizontalFrame0.setFrameShadow(QFrame.Plain)
        self.horizontalFrame0.setLineWidth(1)
        self.horizontalLayout_4 = QHBoxLayout(self.horizontalFrame0)
        self.horizontalLayout_4.setSpacing(1)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.horizontalFrame0Label = QFrame(self.horizontalFrame0)
        self.horizontalFrame0Label.setObjectName(u"horizontalFrame0Label")
        self.horizontalFrame0Label.setFrameShape(QFrame.Panel)
        self.horizontalFrame0Label.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_8 = QHBoxLayout(self.horizontalFrame0Label)
        self.horizontalLayout_8.setSpacing(0)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.horizontalLayout_8.setContentsMargins(0, 0, 4, 0)
        self.label_0Label = QLabel(self.horizontalFrame0Label)
        self.label_0Label.setObjectName(u"label_0Label")
        sizePolicy.setHeightForWidth(self.label_0Label.sizePolicy().hasHeightForWidth())
        self.label_0Label.setSizePolicy(sizePolicy)
        font3 = QFont()
        font3.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font3.setPointSize(20)
        font3.setBold(True)
        self.label_0Label.setFont(font3)
        self.label_0Label.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_8.addWidget(self.label_0Label)

        self.label_0IUpDown = QLabel(self.horizontalFrame0Label)
        self.label_0IUpDown.setObjectName(u"label_0IUpDown")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.label_0IUpDown.sizePolicy().hasHeightForWidth())
        self.label_0IUpDown.setSizePolicy(sizePolicy2)
        self.label_0IUpDown.setMaximumSize(QSize(60, 16777215))
        self.label_0IUpDown.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_0IUpDown.setScaledContents(True)

        self.horizontalLayout_8.addWidget(self.label_0IUpDown)


        self.horizontalLayout_4.addWidget(self.horizontalFrame0Label)

        self.horizontalFrame_0Value = QFrame(self.horizontalFrame0)
        self.horizontalFrame_0Value.setObjectName(u"horizontalFrame_0Value")
        self.horizontalFrame_0Value.setFrameShape(QFrame.Panel)
        self.horizontalFrame_0Value.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.horizontalFrame_0Value)
        self.horizontalLayout_9.setSpacing(0)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(-1, -1, 1, -1)
        self.label_0Value = QLabel(self.horizontalFrame_0Value)
        self.label_0Value.setObjectName(u"label_0Value")
        sizePolicy.setHeightForWidth(self.label_0Value.sizePolicy().hasHeightForWidth())
        self.label_0Value.setSizePolicy(sizePolicy)
        font4 = QFont()
        font4.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font4.setPointSize(36)
        font4.setBold(True)
        self.label_0Value.setFont(font4)
        self.label_0Value.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_9.addWidget(self.label_0Value)

        self.label_0mm = QLabel(self.horizontalFrame_0Value)
        self.label_0mm.setObjectName(u"label_0mm")
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.label_0mm.sizePolicy().hasHeightForWidth())
        self.label_0mm.setSizePolicy(sizePolicy3)
        self.label_0mm.setMinimumSize(QSize(50, 0))
        self.label_0mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_9.addWidget(self.label_0mm)


        self.horizontalLayout_4.addWidget(self.horizontalFrame_0Value)

        self.pushButton_0Set = QPushButton(self.horizontalFrame0)
        self.pushButton_0Set.setObjectName(u"pushButton_0Set")
        sizePolicy.setHeightForWidth(self.pushButton_0Set.sizePolicy().hasHeightForWidth())
        self.pushButton_0Set.setSizePolicy(sizePolicy)
        font5 = QFont()
        font5.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font5.setPointSize(22)
        font5.setBold(True)
        self.pushButton_0Set.setFont(font5)
        self.pushButton_0Set.setStyleSheet(u"color: rgb(255, 0, 0);")
        self.pushButton_0Set.setIconSize(QSize(60, 60))

        self.horizontalLayout_4.addWidget(self.pushButton_0Set)

        self.horizontalLayout_4.setStretch(0, 1)
        self.horizontalLayout_4.setStretch(1, 2)
        self.horizontalLayout_4.setStretch(2, 1)

        self.verticalLayout.addWidget(self.horizontalFrame0)

        self.horizontalFrame_1 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame_1.setObjectName(u"horizontalFrame_1")
        self.horizontalFrame_1.setFrameShape(QFrame.Panel)
        self.horizontalLayout_5 = QHBoxLayout(self.horizontalFrame_1)
        self.horizontalLayout_5.setSpacing(2)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.horizontalFrame1Label = QFrame(self.horizontalFrame_1)
        self.horizontalFrame1Label.setObjectName(u"horizontalFrame1Label")
        self.horizontalFrame1Label.setFrameShape(QFrame.Panel)
        self.horizontalFrame1Label.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_10 = QHBoxLayout(self.horizontalFrame1Label)
        self.horizontalLayout_10.setSpacing(0)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.horizontalLayout_10.setContentsMargins(0, 0, 4, 0)
        self.label_1Label = QLabel(self.horizontalFrame1Label)
        self.label_1Label.setObjectName(u"label_1Label")
        self.label_1Label.setFont(font2)
        self.label_1Label.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_10.addWidget(self.label_1Label)

        self.label_1IUpDown = QLabel(self.horizontalFrame1Label)
        self.label_1IUpDown.setObjectName(u"label_1IUpDown")
        sizePolicy2.setHeightForWidth(self.label_1IUpDown.sizePolicy().hasHeightForWidth())
        self.label_1IUpDown.setSizePolicy(sizePolicy2)
        self.label_1IUpDown.setMaximumSize(QSize(60, 16777215))
        self.label_1IUpDown.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_1IUpDown.setScaledContents(True)

        self.horizontalLayout_10.addWidget(self.label_1IUpDown)


        self.horizontalLayout_5.addWidget(self.horizontalFrame1Label)

        self.horizontalFrame_1Value = QFrame(self.horizontalFrame_1)
        self.horizontalFrame_1Value.setObjectName(u"horizontalFrame_1Value")
        self.horizontalFrame_1Value.setFrameShape(QFrame.Panel)
        self.horizontalFrame_1Value.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_11 = QHBoxLayout(self.horizontalFrame_1Value)
        self.horizontalLayout_11.setSpacing(0)
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.horizontalLayout_11.setContentsMargins(-1, -1, 1, -1)
        self.label_1Value = QLabel(self.horizontalFrame_1Value)
        self.label_1Value.setObjectName(u"label_1Value")
        self.label_1Value.setFont(font4)
        self.label_1Value.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_11.addWidget(self.label_1Value)

        self.label_1mm = QLabel(self.horizontalFrame_1Value)
        self.label_1mm.setObjectName(u"label_1mm")
        sizePolicy2.setHeightForWidth(self.label_1mm.sizePolicy().hasHeightForWidth())
        self.label_1mm.setSizePolicy(sizePolicy2)
        self.label_1mm.setMinimumSize(QSize(50, 0))
        self.label_1mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_11.addWidget(self.label_1mm)


        self.horizontalLayout_5.addWidget(self.horizontalFrame_1Value)

        self.pushButton_1Set = QPushButton(self.horizontalFrame_1)
        self.pushButton_1Set.setObjectName(u"pushButton_1Set")
        sizePolicy.setHeightForWidth(self.pushButton_1Set.sizePolicy().hasHeightForWidth())
        self.pushButton_1Set.setSizePolicy(sizePolicy)
        self.pushButton_1Set.setFont(font5)
        self.pushButton_1Set.setStyleSheet(u"color: rgb(255, 0, 0);")
        self.pushButton_1Set.setIconSize(QSize(60, 60))

        self.horizontalLayout_5.addWidget(self.pushButton_1Set)

        self.horizontalLayout_5.setStretch(0, 1)
        self.horizontalLayout_5.setStretch(1, 2)
        self.horizontalLayout_5.setStretch(2, 1)

        self.verticalLayout.addWidget(self.horizontalFrame_1)

        self.horizontalFrame2 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame2.setObjectName(u"horizontalFrame2")
        self.horizontalFrame2.setFrameShape(QFrame.Panel)
        self.horizontalLayout_6 = QHBoxLayout(self.horizontalFrame2)
        self.horizontalLayout_6.setSpacing(2)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.horizontalFrame2Label = QFrame(self.horizontalFrame2)
        self.horizontalFrame2Label.setObjectName(u"horizontalFrame2Label")
        self.horizontalFrame2Label.setFrameShape(QFrame.Panel)
        self.horizontalFrame2Label.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_12 = QHBoxLayout(self.horizontalFrame2Label)
        self.horizontalLayout_12.setSpacing(0)
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.horizontalLayout_12.setContentsMargins(0, 0, 4, 0)
        self.label_2Label = QLabel(self.horizontalFrame2Label)
        self.label_2Label.setObjectName(u"label_2Label")
        self.label_2Label.setFont(font2)
        self.label_2Label.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_12.addWidget(self.label_2Label)

        self.label_2IUpDown = QLabel(self.horizontalFrame2Label)
        self.label_2IUpDown.setObjectName(u"label_2IUpDown")
        sizePolicy2.setHeightForWidth(self.label_2IUpDown.sizePolicy().hasHeightForWidth())
        self.label_2IUpDown.setSizePolicy(sizePolicy2)
        self.label_2IUpDown.setMaximumSize(QSize(60, 16777215))
        self.label_2IUpDown.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_2IUpDown.setScaledContents(True)

        self.horizontalLayout_12.addWidget(self.label_2IUpDown)


        self.horizontalLayout_6.addWidget(self.horizontalFrame2Label)

        self.horizontalFrame_2Value = QFrame(self.horizontalFrame2)
        self.horizontalFrame_2Value.setObjectName(u"horizontalFrame_2Value")
        self.horizontalFrame_2Value.setFrameShape(QFrame.Panel)
        self.horizontalFrame_2Value.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_13 = QHBoxLayout(self.horizontalFrame_2Value)
        self.horizontalLayout_13.setSpacing(0)
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.horizontalLayout_13.setContentsMargins(-1, -1, 1, -1)
        self.label_2Value = QLabel(self.horizontalFrame_2Value)
        self.label_2Value.setObjectName(u"label_2Value")
        self.label_2Value.setFont(font4)
        self.label_2Value.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_13.addWidget(self.label_2Value)

        self.label_2mm = QLabel(self.horizontalFrame_2Value)
        self.label_2mm.setObjectName(u"label_2mm")
        sizePolicy2.setHeightForWidth(self.label_2mm.sizePolicy().hasHeightForWidth())
        self.label_2mm.setSizePolicy(sizePolicy2)
        self.label_2mm.setMinimumSize(QSize(50, 0))
        self.label_2mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_13.addWidget(self.label_2mm)


        self.horizontalLayout_6.addWidget(self.horizontalFrame_2Value)

        self.pushButton_2Set = QPushButton(self.horizontalFrame2)
        self.pushButton_2Set.setObjectName(u"pushButton_2Set")
        sizePolicy.setHeightForWidth(self.pushButton_2Set.sizePolicy().hasHeightForWidth())
        self.pushButton_2Set.setSizePolicy(sizePolicy)
        self.pushButton_2Set.setFont(font5)
        self.pushButton_2Set.setStyleSheet(u"color: rgb(255, 0, 0);")
        self.pushButton_2Set.setIconSize(QSize(60, 60))

        self.horizontalLayout_6.addWidget(self.pushButton_2Set)

        self.horizontalLayout_6.setStretch(0, 1)
        self.horizontalLayout_6.setStretch(1, 2)
        self.horizontalLayout_6.setStretch(2, 1)

        self.verticalLayout.addWidget(self.horizontalFrame2)

        self.horizontalFrameFR = QFrame(self.horizontalFrame_2)
        self.horizontalFrameFR.setObjectName(u"horizontalFrameFR")
        self.horizontalFrameFR.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.horizontalFrameFR.setFrameShape(QFrame.Panel)
        self.horizontalLayout_7 = QHBoxLayout(self.horizontalFrameFR)
        self.horizontalLayout_7.setSpacing(2)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.pushButton_FR = QPushButton(self.horizontalFrameFR)
        self.pushButton_FR.setObjectName(u"pushButton_FR")
        sizePolicy.setHeightForWidth(self.pushButton_FR.sizePolicy().hasHeightForWidth())
        self.pushButton_FR.setSizePolicy(sizePolicy)
        self.pushButton_FR.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon4 = QIcon()
        icon4.addFile(u":/Medical/Picture/Arrow Double.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_FR.setIcon(icon4)
        self.pushButton_FR.setIconSize(QSize(70, 70))

        self.horizontalLayout_7.addWidget(self.pushButton_FR)

        self.gridFrame = QFrame(self.horizontalFrameFR)
        self.gridFrame.setObjectName(u"gridFrame")
        self.gridFrame.setFrameShape(QFrame.Panel)
        self.gridFrame.setFrameShadow(QFrame.Raised)
        self.gridFrame.setLineWidth(1)
        self.gridLayout = QGridLayout(self.gridFrame)
        self.gridLayout.setSpacing(0)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.label_FR1Lable = QLabel(self.gridFrame)
        self.label_FR1Lable.setObjectName(u"label_FR1Lable")
        sizePolicy4 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.label_FR1Lable.sizePolicy().hasHeightForWidth())
        self.label_FR1Lable.setSizePolicy(sizePolicy4)
        self.label_FR1Lable.setMaximumSize(QSize(16777215, 26))
        self.label_FR1Lable.setFont(font3)
        self.label_FR1Lable.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR1Lable.setFrameShape(QFrame.StyledPanel)
        self.label_FR1Lable.setScaledContents(True)
        self.label_FR1Lable.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_FR1Lable, 0, 0, 1, 2)

        self.label_FR1mm = QLabel(self.gridFrame)
        self.label_FR1mm.setObjectName(u"label_FR1mm")
        sizePolicy2.setHeightForWidth(self.label_FR1mm.sizePolicy().hasHeightForWidth())
        self.label_FR1mm.setSizePolicy(sizePolicy2)
        font6 = QFont()
        font6.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font6.setPointSize(12)
        font6.setBold(True)
        self.label_FR1mm.setFont(font6)
        self.label_FR1mm.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR1mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout.addWidget(self.label_FR1mm, 1, 1, 1, 1)

        self.label_FR1Value = QLabel(self.gridFrame)
        self.label_FR1Value.setObjectName(u"label_FR1Value")
        font7 = QFont()
        font7.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font7.setPointSize(24)
        font7.setBold(True)
        self.label_FR1Value.setFont(font7)
        self.label_FR1Value.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR1Value.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_FR1Value, 1, 0, 1, 1)


        self.horizontalLayout_7.addWidget(self.gridFrame)

        self.gridFrame_2 = QFrame(self.horizontalFrameFR)
        self.gridFrame_2.setObjectName(u"gridFrame_2")
        self.gridFrame_2.setFrameShape(QFrame.Panel)
        self.gridFrame_2.setFrameShadow(QFrame.Raised)
        self.gridFrame_2.setLineWidth(1)
        self.gridLayout_7 = QGridLayout(self.gridFrame_2)
        self.gridLayout_7.setSpacing(0)
        self.gridLayout_7.setObjectName(u"gridLayout_7")
        self.gridLayout_7.setContentsMargins(0, 0, 0, 0)
        self.label_FR2mm = QLabel(self.gridFrame_2)
        self.label_FR2mm.setObjectName(u"label_FR2mm")
        sizePolicy2.setHeightForWidth(self.label_FR2mm.sizePolicy().hasHeightForWidth())
        self.label_FR2mm.setSizePolicy(sizePolicy2)
        self.label_FR2mm.setFont(font6)
        self.label_FR2mm.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR2mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout_7.addWidget(self.label_FR2mm, 1, 1, 1, 1)

        self.label_FR2Value = QLabel(self.gridFrame_2)
        self.label_FR2Value.setObjectName(u"label_FR2Value")
        self.label_FR2Value.setFont(font7)
        self.label_FR2Value.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR2Value.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_FR2Value, 1, 0, 1, 1)

        self.label_FR2Lable = QLabel(self.gridFrame_2)
        self.label_FR2Lable.setObjectName(u"label_FR2Lable")
        sizePolicy4.setHeightForWidth(self.label_FR2Lable.sizePolicy().hasHeightForWidth())
        self.label_FR2Lable.setSizePolicy(sizePolicy4)
        self.label_FR2Lable.setMaximumSize(QSize(16777215, 26))
        self.label_FR2Lable.setFont(font3)
        self.label_FR2Lable.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR2Lable.setFrameShape(QFrame.StyledPanel)
        self.label_FR2Lable.setFrameShadow(QFrame.Plain)
        self.label_FR2Lable.setScaledContents(True)
        self.label_FR2Lable.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_FR2Lable, 0, 0, 1, 2)


        self.horizontalLayout_7.addWidget(self.gridFrame_2)

        self.pushButton_FRSet = QPushButton(self.horizontalFrameFR)
        self.pushButton_FRSet.setObjectName(u"pushButton_FRSet")
        sizePolicy.setHeightForWidth(self.pushButton_FRSet.sizePolicy().hasHeightForWidth())
        self.pushButton_FRSet.setSizePolicy(sizePolicy)
        self.pushButton_FRSet.setFont(font5)
        self.pushButton_FRSet.setStyleSheet(u"background-color: rgb(85, 255, 255);\n"
"color: rgb(255, 0, 0);")
        self.pushButton_FRSet.setIconSize(QSize(60, 60))

        self.horizontalLayout_7.addWidget(self.pushButton_FRSet)

        self.horizontalLayout_7.setStretch(0, 1)
        self.horizontalLayout_7.setStretch(1, 1)
        self.horizontalLayout_7.setStretch(2, 1)
        self.horizontalLayout_7.setStretch(3, 1)

        self.verticalLayout.addWidget(self.horizontalFrameFR)

        self.horizontalFrame16 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame16.setObjectName(u"horizontalFrame16")
        self.horizontalFrame16.setFrameShape(QFrame.Panel)
        self.horizontalLayout_3 = QHBoxLayout(self.horizontalFrame16)
        self.horizontalLayout_3.setSpacing(2)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.pushButton_Zero = QPushButton(self.horizontalFrame16)
        self.pushButton_Zero.setObjectName(u"pushButton_Zero")
        sizePolicy.setHeightForWidth(self.pushButton_Zero.sizePolicy().hasHeightForWidth())
        self.pushButton_Zero.setSizePolicy(sizePolicy)
        self.pushButton_Zero.setFont(font5)
        self.pushButton_Zero.setIconSize(QSize(60, 60))

        self.horizontalLayout_3.addWidget(self.pushButton_Zero)

        self.pushButton_Reset = QPushButton(self.horizontalFrame16)
        self.pushButton_Reset.setObjectName(u"pushButton_Reset")
        sizePolicy.setHeightForWidth(self.pushButton_Reset.sizePolicy().hasHeightForWidth())
        self.pushButton_Reset.setSizePolicy(sizePolicy)
        self.pushButton_Reset.setMinimumSize(QSize(0, 70))
        self.pushButton_Reset.setFont(font5)
        self.pushButton_Reset.setIconSize(QSize(60, 60))

        self.horizontalLayout_3.addWidget(self.pushButton_Reset)

        self.horizontalLayout_3.setStretch(0, 1)
        self.horizontalLayout_3.setStretch(1, 3)

        self.verticalLayout.addWidget(self.horizontalFrame16)

        self.verticalLayout.setStretch(0, 1)
        self.verticalLayout.setStretch(1, 1)
        self.verticalLayout.setStretch(2, 1)
        self.verticalLayout.setStretch(3, 1)
        self.verticalLayout.setStretch(4, 1)
        self.verticalLayout.setStretch(5, 1)

        self.gridLayout_6.addLayout(self.verticalLayout, 0, 0, 1, 1)

        self.gridLayout_6.setColumnStretch(0, 4)
        self.gridLayout_6.setColumnStretch(1, 3)
        self.tabWidget_Main.addTab(self.tab_Run, "")
        self.tab_Paramter = QWidget()
        self.tab_Paramter.setObjectName(u"tab_Paramter")
        self.layoutWidget = QWidget(self.tab_Paramter)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.layoutWidget.setGeometry(QRect(20, 20, 501, 42))
        self.horizontalLayout_17 = QHBoxLayout(self.layoutWidget)
        self.horizontalLayout_17.setObjectName(u"horizontalLayout_17")
        self.horizontalLayout_17.setContentsMargins(0, 0, 0, 0)
        self.radioButton_English = QRadioButton(self.layoutWidget)
        self.radioButton_English.setObjectName(u"radioButton_English")
        self.radioButton_English.setMaximumSize(QSize(200, 40))
        font8 = QFont()
        font8.setFamilies([u"Arial"])
        font8.setPointSize(18)
        font8.setBold(True)
        self.radioButton_English.setFont(font8)
        self.radioButton_English.setCheckable(True)

        self.horizontalLayout_17.addWidget(self.radioButton_English)

        self.radioButton_Chinese = QRadioButton(self.layoutWidget)
        self.radioButton_Chinese.setObjectName(u"radioButton_Chinese")
        self.radioButton_Chinese.setMaximumSize(QSize(200, 40))
        self.radioButton_Chinese.setFont(font8)
        self.radioButton_Chinese.setCheckable(True)

        self.horizontalLayout_17.addWidget(self.radioButton_Chinese)

        self.radioButton_Simplified = QRadioButton(self.layoutWidget)
        self.radioButton_Simplified.setObjectName(u"radioButton_Simplified")
        self.radioButton_Simplified.setMaximumSize(QSize(200, 40))
        self.radioButton_Simplified.setFont(font8)
        self.radioButton_Simplified.setCheckable(True)

        self.horizontalLayout_17.addWidget(self.radioButton_Simplified)

        self.tabWidget_Main.addTab(self.tab_Paramter, "")

        self.horizontalLayout_2.addWidget(self.tabWidget_Main)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        self.tabWidget_Main.setCurrentIndex(0)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Loading Machine", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"0000", None))
        self.label_4.setText(QCoreApplication.translate("MainWindow", u"0000", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"0000", None))
        self.label_8.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"0000", None))
        self.label_11.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf", None))
        self.label_12.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_Up.setText("")
        self.pushButton_Down.setText("")
        self.pushButton_Front.setText("")
        self.pushButton_Rear.setText("")
        self.pushButton_Power.setText(QCoreApplication.translate("MainWindow", u"X1", None))
        self.label_0Label.setText(QCoreApplication.translate("MainWindow", u"\u8d77\u59cb", None))
        self.label_0IUpDown.setText("")
        self.label_0Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_0mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_0Set.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_1Label.setText(QCoreApplication.translate("MainWindow", u"1", None))
        self.label_1IUpDown.setText("")
        self.label_1Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_1mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_1Set.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_2Label.setText(QCoreApplication.translate("MainWindow", u"2", None))
        self.label_2IUpDown.setText("")
        self.label_2Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_2mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_2Set.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.pushButton_FR.setText("")
        self.label_FR1Lable.setText(QCoreApplication.translate("MainWindow", u"1", None))
        self.label_FR1mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FR1Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_FR2mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FR2Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_FR2Lable.setText(QCoreApplication.translate("MainWindow", u"2", None))
        self.pushButton_FRSet.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.pushButton_Zero.setText(QCoreApplication.translate("MainWindow", u"\u6b78\u96f6", None))
        self.pushButton_Reset.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u7f6e", None))
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Run), QCoreApplication.translate("MainWindow", u"\u57f7\u884c", None))
        self.radioButton_English.setText(QCoreApplication.translate("MainWindow", u"English", None))
        self.radioButton_Chinese.setText(QCoreApplication.translate("MainWindow", u"\u7e41\u9ad4", None))
        self.radioButton_Simplified.setText(QCoreApplication.translate("MainWindow", u"\u7b80\u4f53", None))
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Paramter), QCoreApplication.translate("MainWindow", u"\u53c3\u6578", None))
    # retranslateUi


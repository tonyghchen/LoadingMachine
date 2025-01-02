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
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
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
        self.horizontalFrame_2.setGeometry(QRect(430, 20, 1001, 541))
        self.gridLayout_6 = QGridLayout(self.horizontalFrame_2)
        self.gridLayout_6.setObjectName(u"gridLayout_6")
        self.gridLayout_6.setContentsMargins(-1, -1, 0, 0)
        self.gridLayout_6.setColumnStretch(0, 4)
        self.horizontalFrame = QFrame(self.tab_Run)
        self.horizontalFrame.setObjectName(u"horizontalFrame")
        self.horizontalFrame.setGeometry(QRect(0, 0, 1011, 541))
        self.horizontalLayout_4 = QHBoxLayout(self.horizontalFrame)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(-1, -1, 1, -1)
        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.label_GIF = QLabel(self.horizontalFrame)
        self.label_GIF.setObjectName(u"label_GIF")
        self.label_GIF.setFrameShape(QFrame.Panel)
        self.label_GIF.setPixmap(QPixmap(u":/Movie/gif/Process12.gif"))
        self.label_GIF.setAlignment(Qt.AlignCenter)

        self.verticalLayout_3.addWidget(self.label_GIF)

        self.pushButton_Process1 = QPushButton(self.horizontalFrame)
        self.pushButton_Process1.setObjectName(u"pushButton_Process1")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.pushButton_Process1.sizePolicy().hasHeightForWidth())
        self.pushButton_Process1.setSizePolicy(sizePolicy2)
        self.pushButton_Process1.setMaximumSize(QSize(16777215, 80))
        font2 = QFont()
        font2.setFamilies([u"Microsoft JhengHei UI"])
        font2.setPointSize(20)
        font2.setBold(True)
        self.pushButton_Process1.setFont(font2)
        self.pushButton_Process1.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.pushButton_Process1.setIconSize(QSize(80, 80))
        self.pushButton_Process1.setAutoRepeat(True)
        self.pushButton_Process1.setAutoRepeatInterval(50)

        self.verticalLayout_3.addWidget(self.pushButton_Process1)

        self.pushButton_Process2 = QPushButton(self.horizontalFrame)
        self.pushButton_Process2.setObjectName(u"pushButton_Process2")
        self.pushButton_Process2.setMaximumSize(QSize(16777215, 80))
        self.pushButton_Process2.setFont(font2)
        self.pushButton_Process2.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.pushButton_Process2.setIconSize(QSize(80, 80))
        self.pushButton_Process2.setAutoRepeat(True)
        self.pushButton_Process2.setAutoRepeatInterval(50)

        self.verticalLayout_3.addWidget(self.pushButton_Process2)


        self.horizontalLayout_4.addLayout(self.verticalLayout_3)

        self.verticalLayout_Weight = QVBoxLayout()
        self.verticalLayout_Weight.setSpacing(4)
        self.verticalLayout_Weight.setObjectName(u"verticalLayout_Weight")
        self.verticalLayout_Weight.setContentsMargins(-1, 0, -1, 0)
        self.horizontalFrame_Distance1 = QFrame(self.horizontalFrame)
        self.horizontalFrame_Distance1.setObjectName(u"horizontalFrame_Distance1")
        self.horizontalFrame_Distance1.setFrameShape(QFrame.Panel)
        self.horizontalFrame_Distance1.setFrameShadow(QFrame.Plain)
        self.horizontalLayout_15 = QHBoxLayout(self.horizontalFrame_Distance1)
        self.horizontalLayout_15.setObjectName(u"horizontalLayout_15")
        self.label_LoadLable1 = QLabel(self.horizontalFrame_Distance1)
        self.label_LoadLable1.setObjectName(u"label_LoadLable1")
        font3 = QFont()
        font3.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font3.setPointSize(20)
        font3.setBold(True)
        self.label_LoadLable1.setFont(font3)

        self.horizontalLayout_15.addWidget(self.label_LoadLable1)

        self.progressBar1 = QProgressBar(self.horizontalFrame_Distance1)
        self.progressBar1.setObjectName(u"progressBar1")
        self.progressBar1.setFont(font3)
        self.progressBar1.setValue(24)

        self.horizontalLayout_15.addWidget(self.progressBar1)


        self.verticalLayout_Weight.addWidget(self.horizontalFrame_Distance1)

        self.horizontalFrame_Distance2 = QFrame(self.horizontalFrame)
        self.horizontalFrame_Distance2.setObjectName(u"horizontalFrame_Distance2")
        self.horizontalFrame_Distance2.setFrameShape(QFrame.Panel)
        self.horizontalLayout_16 = QHBoxLayout(self.horizontalFrame_Distance2)
        self.horizontalLayout_16.setObjectName(u"horizontalLayout_16")
        self.label_LoadLable2 = QLabel(self.horizontalFrame_Distance2)
        self.label_LoadLable2.setObjectName(u"label_LoadLable2")
        self.label_LoadLable2.setFont(font3)

        self.horizontalLayout_16.addWidget(self.label_LoadLable2)

        self.progressBar2 = QProgressBar(self.horizontalFrame_Distance2)
        self.progressBar2.setObjectName(u"progressBar2")
        self.progressBar2.setFont(font3)
        self.progressBar2.setValue(24)

        self.horizontalLayout_16.addWidget(self.progressBar2)


        self.verticalLayout_Weight.addWidget(self.horizontalFrame_Distance2)

        self.horizontalFrame_Distance3 = QFrame(self.horizontalFrame)
        self.horizontalFrame_Distance3.setObjectName(u"horizontalFrame_Distance3")
        self.horizontalFrame_Distance3.setFrameShape(QFrame.Panel)
        self.horizontalLayout_19 = QHBoxLayout(self.horizontalFrame_Distance3)
        self.horizontalLayout_19.setObjectName(u"horizontalLayout_19")
        self.label_LoadLable3 = QLabel(self.horizontalFrame_Distance3)
        self.label_LoadLable3.setObjectName(u"label_LoadLable3")
        self.label_LoadLable3.setFont(font3)

        self.horizontalLayout_19.addWidget(self.label_LoadLable3)

        self.progressBar3 = QProgressBar(self.horizontalFrame_Distance3)
        self.progressBar3.setObjectName(u"progressBar3")
        self.progressBar3.setFont(font3)
        self.progressBar3.setValue(24)

        self.horizontalLayout_19.addWidget(self.progressBar3)


        self.verticalLayout_Weight.addWidget(self.horizontalFrame_Distance3)

        self.horizontalFrame_Distance4 = QFrame(self.horizontalFrame)
        self.horizontalFrame_Distance4.setObjectName(u"horizontalFrame_Distance4")
        self.horizontalFrame_Distance4.setFrameShape(QFrame.Panel)
        self.horizontalLayout_18 = QHBoxLayout(self.horizontalFrame_Distance4)
        self.horizontalLayout_18.setObjectName(u"horizontalLayout_18")
        self.label_LoadLable4 = QLabel(self.horizontalFrame_Distance4)
        self.label_LoadLable4.setObjectName(u"label_LoadLable4")
        self.label_LoadLable4.setFont(font3)

        self.horizontalLayout_18.addWidget(self.label_LoadLable4)

        self.progressBar4 = QProgressBar(self.horizontalFrame_Distance4)
        self.progressBar4.setObjectName(u"progressBar4")
        self.progressBar4.setFont(font3)
        self.progressBar4.setValue(24)

        self.horizontalLayout_18.addWidget(self.progressBar4)


        self.verticalLayout_Weight.addWidget(self.horizontalFrame_Distance4)

        self.horizontalLayout_Value = QHBoxLayout()
        self.horizontalLayout_Value.setSpacing(2)
        self.horizontalLayout_Value.setObjectName(u"horizontalLayout_Value")
        self.horizontalLayout_Value.setContentsMargins(-1, 0, 0, 0)
        self.gridFrame_UpDownValue = QFrame(self.horizontalFrame)
        self.gridFrame_UpDownValue.setObjectName(u"gridFrame_UpDownValue")
        self.gridFrame_UpDownValue.setFrameShape(QFrame.Panel)
        self.gridLayout_4 = QGridLayout(self.gridFrame_UpDownValue)
        self.gridLayout_4.setSpacing(0)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.gridLayout_4.setContentsMargins(0, 0, 0, 0)
        self.label_UpDownValue1 = QLabel(self.gridFrame_UpDownValue)
        self.label_UpDownValue1.setObjectName(u"label_UpDownValue1")
        font4 = QFont()
        font4.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font4.setPointSize(36)
        font4.setBold(True)
        self.label_UpDownValue1.setFont(font4)
        self.label_UpDownValue1.setAlignment(Qt.AlignCenter)

        self.gridLayout_4.addWidget(self.label_UpDownValue1, 1, 0, 1, 1)

        self.label_9 = QLabel(self.gridFrame_UpDownValue)
        self.label_9.setObjectName(u"label_9")
        self.label_9.setMaximumSize(QSize(50, 16777215))
        self.label_9.setAlignment(Qt.AlignBottom|Qt.AlignRight|Qt.AlignTrailing)

        self.gridLayout_4.addWidget(self.label_9, 1, 1, 1, 1)

        self.label_3 = QLabel(self.gridFrame_UpDownValue)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setFrameShape(QFrame.Panel)
        self.label_3.setFrameShadow(QFrame.Raised)
        self.label_3.setPixmap(QPixmap(u":/Medical/Picture/arrow up down1.png"))
        self.label_3.setAlignment(Qt.AlignCenter)

        self.gridLayout_4.addWidget(self.label_3, 0, 0, 1, 2)


        self.horizontalLayout_Value.addWidget(self.gridFrame_UpDownValue)

        self.gridFrame_FRValue = QFrame(self.horizontalFrame)
        self.gridFrame_FRValue.setObjectName(u"gridFrame_FRValue")
        self.gridFrame_FRValue.setFrameShape(QFrame.Panel)
        self.gridLayout_3 = QGridLayout(self.gridFrame_FRValue)
        self.gridLayout_3.setSpacing(0)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.label_6 = QLabel(self.gridFrame_FRValue)
        self.label_6.setObjectName(u"label_6")
        self.label_6.setMaximumSize(QSize(50, 16777215))
        self.label_6.setAlignment(Qt.AlignBottom|Qt.AlignRight|Qt.AlignTrailing)

        self.gridLayout_3.addWidget(self.label_6, 1, 1, 1, 1)

        self.label_FrontRearValue1 = QLabel(self.gridFrame_FRValue)
        self.label_FrontRearValue1.setObjectName(u"label_FrontRearValue1")
        self.label_FrontRearValue1.setFont(font4)
        self.label_FrontRearValue1.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_FrontRearValue1, 1, 0, 1, 1)

        self.label_2 = QLabel(self.gridFrame_FRValue)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setFrameShape(QFrame.Panel)
        self.label_2.setFrameShadow(QFrame.Raised)
        self.label_2.setPixmap(QPixmap(u":/Medical/Picture/Arrow Right Left 45.png"))
        self.label_2.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_2, 0, 0, 1, 2)


        self.horizontalLayout_Value.addWidget(self.gridFrame_FRValue)


        self.verticalLayout_Weight.addLayout(self.horizontalLayout_Value)


        self.horizontalLayout_4.addLayout(self.verticalLayout_Weight)

        self.horizontalLayout_4.setStretch(0, 2)
        self.horizontalLayout_4.setStretch(1, 3)
        self.tabWidget_Main.addTab(self.tab_Run, "")
        self.tab_Paramter = QWidget()
        self.tab_Paramter.setObjectName(u"tab_Paramter")
        self.gridLayoutWidget = QWidget(self.tab_Paramter)
        self.gridLayoutWidget.setObjectName(u"gridLayoutWidget")
        self.gridLayoutWidget.setGeometry(QRect(10, 80, 1001, 291))
        self.gridLayout_2 = QGridLayout(self.gridLayoutWidget)
        self.gridLayout_2.setSpacing(1)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.pushButton_Updown2 = QPushButton(self.gridLayoutWidget)
        self.pushButton_Updown2.setObjectName(u"pushButton_Updown2")
        sizePolicy.setHeightForWidth(self.pushButton_Updown2.sizePolicy().hasHeightForWidth())
        self.pushButton_Updown2.setSizePolicy(sizePolicy)
        self.pushButton_Updown2.setMaximumSize(QSize(180, 16777215))
        font5 = QFont()
        font5.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font5.setPointSize(30)
        font5.setBold(True)
        self.pushButton_Updown2.setFont(font5)
        self.pushButton_Updown2.setStyleSheet(u"")
        self.pushButton_Updown2.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_Updown2, 2, 3, 1, 1)

        self.label_1Label = QLabel(self.gridLayoutWidget)
        self.label_1Label.setObjectName(u"label_1Label")
        self.label_1Label.setFont(font5)
        self.label_1Label.setFrameShape(QFrame.Panel)
        self.label_1Label.setFrameShadow(QFrame.Raised)
        self.label_1Label.setAlignment(Qt.AlignCenter)

        self.gridLayout_2.addWidget(self.label_1Label, 0, 0, 2, 1)

        self.horizontalFrame_2ValueUpDown = QFrame(self.gridLayoutWidget)
        self.horizontalFrame_2ValueUpDown.setObjectName(u"horizontalFrame_2ValueUpDown")
        self.horizontalFrame_2ValueUpDown.setFrameShape(QFrame.Panel)
        self.horizontalFrame_2ValueUpDown.setFrameShadow(QFrame.Raised)
        self.horizontalFrame_2ValueUpDown.setLineWidth(1)
        self.gridLayout_7 = QGridLayout(self.horizontalFrame_2ValueUpDown)
        self.gridLayout_7.setSpacing(0)
        self.gridLayout_7.setObjectName(u"gridLayout_7")
        self.gridLayout_7.setContentsMargins(0, 0, 0, 0)
        self.label_FR2mm = QLabel(self.horizontalFrame_2ValueUpDown)
        self.label_FR2mm.setObjectName(u"label_FR2mm")
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.label_FR2mm.sizePolicy().hasHeightForWidth())
        self.label_FR2mm.setSizePolicy(sizePolicy3)
        self.label_FR2mm.setMinimumSize(QSize(50, 0))
        font6 = QFont()
        font6.setFamilies([u"Microsoft JhengHei UI"])
        font6.setPointSize(16)
        font6.setBold(True)
        self.label_FR2mm.setFont(font6)
        self.label_FR2mm.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR2mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout_7.addWidget(self.label_FR2mm, 0, 1, 1, 1)

        self.label_FrontRear2 = QLabel(self.horizontalFrame_2ValueUpDown)
        self.label_FrontRear2.setObjectName(u"label_FrontRear2")
        self.label_FrontRear2.setMinimumSize(QSize(200, 0))
        self.label_FrontRear2.setFont(font4)
        self.label_FrontRear2.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FrontRear2.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_FrontRear2, 0, 0, 1, 1)


        self.gridLayout_2.addWidget(self.horizontalFrame_2ValueUpDown, 3, 2, 1, 1)

        self.pushButton_HomeFrontRear = QPushButton(self.gridLayoutWidget)
        self.pushButton_HomeFrontRear.setObjectName(u"pushButton_HomeFrontRear")
        sizePolicy.setHeightForWidth(self.pushButton_HomeFrontRear.sizePolicy().hasHeightForWidth())
        self.pushButton_HomeFrontRear.setSizePolicy(sizePolicy)
        self.pushButton_HomeFrontRear.setMinimumSize(QSize(0, 70))
        font7 = QFont()
        font7.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font7.setPointSize(22)
        font7.setBold(True)
        self.pushButton_HomeFrontRear.setFont(font7)
        self.pushButton_HomeFrontRear.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.pushButton_HomeFrontRear.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_HomeFrontRear, 3, 5, 1, 1)

        self.label_2Label = QLabel(self.gridLayoutWidget)
        self.label_2Label.setObjectName(u"label_2Label")
        self.label_2Label.setFont(font5)
        self.label_2Label.setFrameShape(QFrame.Panel)
        self.label_2Label.setFrameShadow(QFrame.Raised)
        self.label_2Label.setAlignment(Qt.AlignCenter)

        self.gridLayout_2.addWidget(self.label_2Label, 2, 0, 2, 1)

        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setSpacing(1)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.pushButton_Rear = QPushButton(self.gridLayoutWidget)
        self.pushButton_Rear.setObjectName(u"pushButton_Rear")
        sizePolicy4 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.pushButton_Rear.sizePolicy().hasHeightForWidth())
        self.pushButton_Rear.setSizePolicy(sizePolicy4)
        self.pushButton_Rear.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon = QIcon()
        icon.addFile(u":/Medical/Picture/Arrow Right45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Rear.setIcon(icon)
        self.pushButton_Rear.setIconSize(QSize(80, 80))
        self.pushButton_Rear.setAutoRepeat(True)
        self.pushButton_Rear.setAutoRepeatInterval(50)

        self.horizontalLayout_8.addWidget(self.pushButton_Rear)

        self.pushButton_Front = QPushButton(self.gridLayoutWidget)
        self.pushButton_Front.setObjectName(u"pushButton_Front")
        sizePolicy.setHeightForWidth(self.pushButton_Front.sizePolicy().hasHeightForWidth())
        self.pushButton_Front.setSizePolicy(sizePolicy)
        self.pushButton_Front.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon1 = QIcon()
        icon1.addFile(u":/Medical/Picture/Arrow Leftt45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Front.setIcon(icon1)
        self.pushButton_Front.setIconSize(QSize(80, 80))
        self.pushButton_Front.setAutoRepeat(True)
        self.pushButton_Front.setAutoRepeatInterval(50)

        self.horizontalLayout_8.addWidget(self.pushButton_Front)

        self.pushButton_PowerFrontRear = QPushButton(self.gridLayoutWidget)
        self.pushButton_PowerFrontRear.setObjectName(u"pushButton_PowerFrontRear")
        sizePolicy.setHeightForWidth(self.pushButton_PowerFrontRear.sizePolicy().hasHeightForWidth())
        self.pushButton_PowerFrontRear.setSizePolicy(sizePolicy)
        self.pushButton_PowerFrontRear.setMinimumSize(QSize(0, 0))
        font8 = QFont()
        font8.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font8.setPointSize(24)
        font8.setBold(True)
        self.pushButton_PowerFrontRear.setFont(font8)
        self.pushButton_PowerFrontRear.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.pushButton_PowerFrontRear.setIconSize(QSize(80, 80))

        self.horizontalLayout_8.addWidget(self.pushButton_PowerFrontRear)


        self.gridLayout_2.addLayout(self.horizontalLayout_8, 2, 5, 1, 1)

        self.horizontalFrame_1Value = QFrame(self.gridLayoutWidget)
        self.horizontalFrame_1Value.setObjectName(u"horizontalFrame_1Value")
        self.horizontalFrame_1Value.setFrameShape(QFrame.Panel)
        self.horizontalFrame_1Value.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_11 = QHBoxLayout(self.horizontalFrame_1Value)
        self.horizontalLayout_11.setSpacing(0)
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.horizontalLayout_11.setContentsMargins(0, 0, 0, 0)
        self.label_Updown1 = QLabel(self.horizontalFrame_1Value)
        self.label_Updown1.setObjectName(u"label_Updown1")
        self.label_Updown1.setMinimumSize(QSize(200, 0))
        self.label_Updown1.setFont(font4)
        self.label_Updown1.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_11.addWidget(self.label_Updown1)

        self.label_1mm = QLabel(self.horizontalFrame_1Value)
        self.label_1mm.setObjectName(u"label_1mm")
        sizePolicy3.setHeightForWidth(self.label_1mm.sizePolicy().hasHeightForWidth())
        self.label_1mm.setSizePolicy(sizePolicy3)
        self.label_1mm.setMinimumSize(QSize(50, 0))
        self.label_1mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_11.addWidget(self.label_1mm)


        self.gridLayout_2.addWidget(self.horizontalFrame_1Value, 0, 2, 1, 1)

        self.horizontalFrame_1ValueUpDown = QFrame(self.gridLayoutWidget)
        self.horizontalFrame_1ValueUpDown.setObjectName(u"horizontalFrame_1ValueUpDown")
        self.horizontalFrame_1ValueUpDown.setFrameShape(QFrame.Panel)
        self.horizontalFrame_1ValueUpDown.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.horizontalFrame_1ValueUpDown)
        self.horizontalLayout_9.setSpacing(0)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(0, 0, 0, 0)
        self.label_FrontRear1 = QLabel(self.horizontalFrame_1ValueUpDown)
        self.label_FrontRear1.setObjectName(u"label_FrontRear1")
        self.label_FrontRear1.setMinimumSize(QSize(200, 0))
        self.label_FrontRear1.setFont(font4)
        self.label_FrontRear1.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FrontRear1.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_9.addWidget(self.label_FrontRear1)

        self.label_FR1mm = QLabel(self.horizontalFrame_1ValueUpDown)
        self.label_FR1mm.setObjectName(u"label_FR1mm")
        sizePolicy3.setHeightForWidth(self.label_FR1mm.sizePolicy().hasHeightForWidth())
        self.label_FR1mm.setSizePolicy(sizePolicy3)
        self.label_FR1mm.setMinimumSize(QSize(50, 0))
        self.label_FR1mm.setFont(font1)
        self.label_FR1mm.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR1mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_9.addWidget(self.label_FR1mm)


        self.gridLayout_2.addWidget(self.horizontalFrame_1ValueUpDown, 1, 2, 1, 1)

        self.pushButton_HomeUpDown = QPushButton(self.gridLayoutWidget)
        self.pushButton_HomeUpDown.setObjectName(u"pushButton_HomeUpDown")
        sizePolicy.setHeightForWidth(self.pushButton_HomeUpDown.sizePolicy().hasHeightForWidth())
        self.pushButton_HomeUpDown.setSizePolicy(sizePolicy)
        self.pushButton_HomeUpDown.setFont(font7)
        self.pushButton_HomeUpDown.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_HomeUpDown, 3, 4, 1, 1)

        self.pushButton_FrontRear2 = QPushButton(self.gridLayoutWidget)
        self.pushButton_FrontRear2.setObjectName(u"pushButton_FrontRear2")
        sizePolicy5 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.pushButton_FrontRear2.sizePolicy().hasHeightForWidth())
        self.pushButton_FrontRear2.setSizePolicy(sizePolicy5)
        self.pushButton_FrontRear2.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon2 = QIcon()
        icon2.addFile(u":/Medical/Picture/Arrow Double.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_FrontRear2.setIcon(icon2)
        self.pushButton_FrontRear2.setIconSize(QSize(70, 70))

        self.gridLayout_2.addWidget(self.pushButton_FrontRear2, 3, 1, 1, 1)

        self.pushButton_FRSet1 = QPushButton(self.gridLayoutWidget)
        self.pushButton_FRSet1.setObjectName(u"pushButton_FRSet1")
        sizePolicy.setHeightForWidth(self.pushButton_FRSet1.sizePolicy().hasHeightForWidth())
        self.pushButton_FRSet1.setSizePolicy(sizePolicy)
        self.pushButton_FRSet1.setMaximumSize(QSize(180, 16777215))
        self.pushButton_FRSet1.setFont(font5)
        self.pushButton_FRSet1.setStyleSheet(u"background-color: rgb(85, 255, 255);\n"
"color: rgb(255, 0, 0);")
        self.pushButton_FRSet1.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_FRSet1, 1, 3, 1, 1)

        self.pushButton_Updown1 = QPushButton(self.gridLayoutWidget)
        self.pushButton_Updown1.setObjectName(u"pushButton_Updown1")
        sizePolicy.setHeightForWidth(self.pushButton_Updown1.sizePolicy().hasHeightForWidth())
        self.pushButton_Updown1.setSizePolicy(sizePolicy)
        self.pushButton_Updown1.setMaximumSize(QSize(180, 16777215))
        self.pushButton_Updown1.setFont(font5)
        self.pushButton_Updown1.setStyleSheet(u"")
        self.pushButton_Updown1.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_Updown1, 0, 3, 1, 1)

        self.label_4 = QLabel(self.gridLayoutWidget)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setFrameShape(QFrame.Panel)
        self.label_4.setFrameShadow(QFrame.Raised)
        self.label_4.setPixmap(QPixmap(u":/Medical/Picture/arrow up down1.png"))
        self.label_4.setScaledContents(False)
        self.label_4.setAlignment(Qt.AlignCenter)

        self.gridLayout_2.addWidget(self.label_4, 0, 4, 1, 1)

        self.label_11 = QLabel(self.gridLayoutWidget)
        self.label_11.setObjectName(u"label_11")
        self.label_11.setStyleSheet(u"background-color: rgb(85, 255, 255);\n"
"")
        self.label_11.setFrameShape(QFrame.Panel)
        self.label_11.setFrameShadow(QFrame.Raised)
        self.label_11.setPixmap(QPixmap(u":/Medical/Picture/Arrow Right Left 45.png"))
        self.label_11.setAlignment(Qt.AlignCenter)

        self.gridLayout_2.addWidget(self.label_11, 0, 5, 1, 1)

        self.gridFrame_UpDownValue_2 = QFrame(self.gridLayoutWidget)
        self.gridFrame_UpDownValue_2.setObjectName(u"gridFrame_UpDownValue_2")
        self.gridFrame_UpDownValue_2.setFrameShape(QFrame.Panel)
        self.gridLayout_5 = QGridLayout(self.gridFrame_UpDownValue_2)
        self.gridLayout_5.setSpacing(0)
        self.gridLayout_5.setObjectName(u"gridLayout_5")
        self.gridLayout_5.setContentsMargins(0, 0, 0, 0)
        self.label_10 = QLabel(self.gridFrame_UpDownValue_2)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setMaximumSize(QSize(50, 16777215))
        self.label_10.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_10.setAlignment(Qt.AlignBottom|Qt.AlignRight|Qt.AlignTrailing)

        self.gridLayout_5.addWidget(self.label_10, 1, 1, 1, 1)

        self.label_FrontRearValue2 = QLabel(self.gridFrame_UpDownValue_2)
        self.label_FrontRearValue2.setObjectName(u"label_FrontRearValue2")
        self.label_FrontRearValue2.setFont(font4)
        self.label_FrontRearValue2.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FrontRearValue2.setAlignment(Qt.AlignCenter)

        self.gridLayout_5.addWidget(self.label_FrontRearValue2, 1, 0, 1, 1)


        self.gridLayout_2.addWidget(self.gridFrame_UpDownValue_2, 1, 5, 1, 1)

        self.pushButton_FRSet2 = QPushButton(self.gridLayoutWidget)
        self.pushButton_FRSet2.setObjectName(u"pushButton_FRSet2")
        sizePolicy.setHeightForWidth(self.pushButton_FRSet2.sizePolicy().hasHeightForWidth())
        self.pushButton_FRSet2.setSizePolicy(sizePolicy)
        self.pushButton_FRSet2.setMaximumSize(QSize(180, 16777215))
        self.pushButton_FRSet2.setFont(font5)
        self.pushButton_FRSet2.setStyleSheet(u"background-color: rgb(85, 255, 255);\n"
"color: rgb(255, 0, 0);")
        self.pushButton_FRSet2.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_FRSet2, 3, 3, 1, 1)

        self.horizontalFrameDirection = QFrame(self.gridLayoutWidget)
        self.horizontalFrameDirection.setObjectName(u"horizontalFrameDirection")
        self.horizontalFrameDirection.setFrameShape(QFrame.Panel)
        self.horizontalFrameDirection.setLineWidth(1)
        self.horizontalLayout = QHBoxLayout(self.horizontalFrameDirection)
        self.horizontalLayout.setSpacing(1)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.pushButton_Up = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Up.setObjectName(u"pushButton_Up")
        sizePolicy4.setHeightForWidth(self.pushButton_Up.sizePolicy().hasHeightForWidth())
        self.pushButton_Up.setSizePolicy(sizePolicy4)
        icon3 = QIcon()
        icon3.addFile(u":/Medical/Picture/up arrow.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Up.setIcon(icon3)
        self.pushButton_Up.setIconSize(QSize(80, 80))
        self.pushButton_Up.setAutoRepeat(True)
        self.pushButton_Up.setAutoRepeatInterval(50)

        self.horizontalLayout.addWidget(self.pushButton_Up)

        self.pushButton_Down = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Down.setObjectName(u"pushButton_Down")
        sizePolicy4.setHeightForWidth(self.pushButton_Down.sizePolicy().hasHeightForWidth())
        self.pushButton_Down.setSizePolicy(sizePolicy4)
        icon4 = QIcon()
        icon4.addFile(u":/Medical/Picture/down arrow.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Down.setIcon(icon4)
        self.pushButton_Down.setIconSize(QSize(80, 80))
        self.pushButton_Down.setAutoRepeat(True)
        self.pushButton_Down.setAutoRepeatInterval(50)

        self.horizontalLayout.addWidget(self.pushButton_Down)

        self.pushButton_PowerUpDown = QPushButton(self.horizontalFrameDirection)
        self.pushButton_PowerUpDown.setObjectName(u"pushButton_PowerUpDown")
        sizePolicy.setHeightForWidth(self.pushButton_PowerUpDown.sizePolicy().hasHeightForWidth())
        self.pushButton_PowerUpDown.setSizePolicy(sizePolicy)
        self.pushButton_PowerUpDown.setMinimumSize(QSize(0, 0))
        self.pushButton_PowerUpDown.setFont(font8)
        self.pushButton_PowerUpDown.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_PowerUpDown)


        self.gridLayout_2.addWidget(self.horizontalFrameDirection, 2, 4, 1, 1)

        self.horizontalFrame_2Value = QFrame(self.gridLayoutWidget)
        self.horizontalFrame_2Value.setObjectName(u"horizontalFrame_2Value")
        self.horizontalFrame_2Value.setFrameShape(QFrame.Panel)
        self.horizontalFrame_2Value.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_13 = QHBoxLayout(self.horizontalFrame_2Value)
        self.horizontalLayout_13.setSpacing(0)
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.horizontalLayout_13.setContentsMargins(0, 0, 0, 0)
        self.label_Updown2 = QLabel(self.horizontalFrame_2Value)
        self.label_Updown2.setObjectName(u"label_Updown2")
        self.label_Updown2.setMinimumSize(QSize(200, 0))
        self.label_Updown2.setFont(font4)
        self.label_Updown2.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_13.addWidget(self.label_Updown2)

        self.label_2mm = QLabel(self.horizontalFrame_2Value)
        self.label_2mm.setObjectName(u"label_2mm")
        sizePolicy3.setHeightForWidth(self.label_2mm.sizePolicy().hasHeightForWidth())
        self.label_2mm.setSizePolicy(sizePolicy3)
        self.label_2mm.setMinimumSize(QSize(50, 0))
        self.label_2mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_13.addWidget(self.label_2mm)


        self.gridLayout_2.addWidget(self.horizontalFrame_2Value, 2, 2, 1, 1)

        self.gridFrame_FRValue_2 = QFrame(self.gridLayoutWidget)
        self.gridFrame_FRValue_2.setObjectName(u"gridFrame_FRValue_2")
        self.gridFrame_FRValue_2.setFrameShape(QFrame.Panel)
        self.gridLayout_9 = QGridLayout(self.gridFrame_FRValue_2)
        self.gridLayout_9.setSpacing(0)
        self.gridLayout_9.setObjectName(u"gridLayout_9")
        self.gridLayout_9.setContentsMargins(0, 0, 0, 0)
        self.label_8 = QLabel(self.gridFrame_FRValue_2)
        self.label_8.setObjectName(u"label_8")
        self.label_8.setMaximumSize(QSize(50, 16777215))
        self.label_8.setAlignment(Qt.AlignBottom|Qt.AlignRight|Qt.AlignTrailing)

        self.gridLayout_9.addWidget(self.label_8, 1, 1, 1, 1)

        self.label_UpDownValue2 = QLabel(self.gridFrame_FRValue_2)
        self.label_UpDownValue2.setObjectName(u"label_UpDownValue2")
        self.label_UpDownValue2.setFont(font4)
        self.label_UpDownValue2.setAlignment(Qt.AlignCenter)

        self.gridLayout_9.addWidget(self.label_UpDownValue2, 1, 0, 1, 1)


        self.gridLayout_2.addWidget(self.gridFrame_FRValue_2, 1, 4, 1, 1)

        self.pushButton_FrontRear1 = QPushButton(self.gridLayoutWidget)
        self.pushButton_FrontRear1.setObjectName(u"pushButton_FrontRear1")
        sizePolicy5.setHeightForWidth(self.pushButton_FrontRear1.sizePolicy().hasHeightForWidth())
        self.pushButton_FrontRear1.setSizePolicy(sizePolicy5)
        self.pushButton_FrontRear1.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.pushButton_FrontRear1.setIcon(icon2)
        self.pushButton_FrontRear1.setIconSize(QSize(70, 70))

        self.gridLayout_2.addWidget(self.pushButton_FrontRear1, 1, 1, 1, 1)

        self.pushButton_UpDown1 = QPushButton(self.gridLayoutWidget)
        self.pushButton_UpDown1.setObjectName(u"pushButton_UpDown1")
        sizePolicy5.setHeightForWidth(self.pushButton_UpDown1.sizePolicy().hasHeightForWidth())
        self.pushButton_UpDown1.setSizePolicy(sizePolicy5)
        self.pushButton_UpDown1.setStyleSheet(u"")
        icon5 = QIcon()
        icon5.addFile(u":/Medical/Picture/arrow up down.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_UpDown1.setIcon(icon5)
        self.pushButton_UpDown1.setIconSize(QSize(70, 70))

        self.gridLayout_2.addWidget(self.pushButton_UpDown1, 0, 1, 1, 1)

        self.pushButton_UpDown2 = QPushButton(self.gridLayoutWidget)
        self.pushButton_UpDown2.setObjectName(u"pushButton_UpDown2")
        sizePolicy5.setHeightForWidth(self.pushButton_UpDown2.sizePolicy().hasHeightForWidth())
        self.pushButton_UpDown2.setSizePolicy(sizePolicy5)
        self.pushButton_UpDown2.setStyleSheet(u"")
        self.pushButton_UpDown2.setIcon(icon5)
        self.pushButton_UpDown2.setIconSize(QSize(70, 70))

        self.gridLayout_2.addWidget(self.pushButton_UpDown2, 2, 1, 1, 1)

        self.horizontalLayoutWidget_2 = QWidget(self.tab_Paramter)
        self.horizontalLayoutWidget_2.setObjectName(u"horizontalLayoutWidget_2")
        self.horizontalLayoutWidget_2.setGeometry(QRect(10, 0, 468, 61))
        self.horizontalLayout_7 = QHBoxLayout(self.horizontalLayoutWidget_2)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.radioButton_English = QRadioButton(self.horizontalLayoutWidget_2)
        self.radioButton_English.setObjectName(u"radioButton_English")
        self.radioButton_English.setMaximumSize(QSize(200, 40))
        font9 = QFont()
        font9.setFamilies([u"Arial"])
        font9.setPointSize(18)
        font9.setBold(True)
        self.radioButton_English.setFont(font9)
        self.radioButton_English.setCheckable(True)

        self.horizontalLayout_7.addWidget(self.radioButton_English)

        self.radioButton_Chinese = QRadioButton(self.horizontalLayoutWidget_2)
        self.radioButton_Chinese.setObjectName(u"radioButton_Chinese")
        self.radioButton_Chinese.setMaximumSize(QSize(200, 40))
        self.radioButton_Chinese.setFont(font9)
        self.radioButton_Chinese.setCheckable(True)

        self.horizontalLayout_7.addWidget(self.radioButton_Chinese)

        self.radioButton_Simplified = QRadioButton(self.horizontalLayoutWidget_2)
        self.radioButton_Simplified.setObjectName(u"radioButton_Simplified")
        self.radioButton_Simplified.setMaximumSize(QSize(200, 40))
        self.radioButton_Simplified.setFont(font9)
        self.radioButton_Simplified.setCheckable(True)

        self.horizontalLayout_7.addWidget(self.radioButton_Simplified)

        self.tabWidget_Main.addTab(self.tab_Paramter, "")

        self.horizontalLayout_2.addWidget(self.tabWidget_Main)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        self.tabWidget_Main.setCurrentIndex(1)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Loading Machine", None))
        self.label_GIF.setText("")
        self.pushButton_Process1.setText(QCoreApplication.translate("MainWindow", u"Process-1", None))
        self.pushButton_Process2.setText(QCoreApplication.translate("MainWindow", u"Process-2", None))
        self.label_LoadLable1.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf1", None))
        self.progressBar1.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_LoadLable2.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf2", None))
        self.progressBar2.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_LoadLable3.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf3", None))
        self.progressBar3.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_LoadLable4.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf4", None))
        self.progressBar4.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_UpDownValue1.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_3.setText("")
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FrontRearValue1.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.label_2.setText("")
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Run), QCoreApplication.translate("MainWindow", u"\u57f7\u884c", None))
        self.pushButton_Updown2.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_1Label.setText(QCoreApplication.translate("MainWindow", u"1", None))
        self.label_FR2mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FrontRear2.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.pushButton_HomeFrontRear.setText(QCoreApplication.translate("MainWindow", u"\u6b78\u4f4d", None))
        self.label_2Label.setText(QCoreApplication.translate("MainWindow", u"2", None))
        self.pushButton_Rear.setText("")
        self.pushButton_Front.setText("")
        self.pushButton_PowerFrontRear.setText(QCoreApplication.translate("MainWindow", u"X1", None))
        self.label_Updown1.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_1mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FrontRear1.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_FR1mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_HomeUpDown.setText(QCoreApplication.translate("MainWindow", u"\u6b78\u4f4d", None))
        self.pushButton_FrontRear2.setText("")
        self.pushButton_FRSet1.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.pushButton_Updown1.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_4.setText("")
        self.label_11.setText("")
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FrontRearValue2.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.pushButton_FRSet2.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.pushButton_Up.setText("")
        self.pushButton_Down.setText("")
        self.pushButton_PowerUpDown.setText(QCoreApplication.translate("MainWindow", u"X1", None))
        self.label_Updown2.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_2mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_8.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_UpDownValue2.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.pushButton_FrontRear1.setText("")
        self.pushButton_UpDown1.setText("")
        self.pushButton_UpDown2.setText("")
        self.radioButton_English.setText(QCoreApplication.translate("MainWindow", u"English", None))
        self.radioButton_Chinese.setText(QCoreApplication.translate("MainWindow", u"\u7e41\u9ad4", None))
        self.radioButton_Simplified.setText(QCoreApplication.translate("MainWindow", u"\u7b80\u4f53", None))
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Paramter), QCoreApplication.translate("MainWindow", u"\u53c3\u6578", None))
    # retranslateUi


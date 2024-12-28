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
        self.label_GIF.setPixmap(QPixmap(u":/Movie/gif/Process2-unscreen.gif"))

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

        self.progressBar = QProgressBar(self.horizontalFrame_Distance1)
        self.progressBar.setObjectName(u"progressBar")
        self.progressBar.setFont(font3)
        self.progressBar.setValue(24)

        self.horizontalLayout_15.addWidget(self.progressBar)


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

        self.progressBar_2 = QProgressBar(self.horizontalFrame_Distance2)
        self.progressBar_2.setObjectName(u"progressBar_2")
        self.progressBar_2.setFont(font3)
        self.progressBar_2.setValue(24)

        self.horizontalLayout_16.addWidget(self.progressBar_2)


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

        self.progressBar_4 = QProgressBar(self.horizontalFrame_Distance3)
        self.progressBar_4.setObjectName(u"progressBar_4")
        self.progressBar_4.setFont(font3)
        self.progressBar_4.setValue(24)

        self.horizontalLayout_19.addWidget(self.progressBar_4)


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

        self.progressBar_3 = QProgressBar(self.horizontalFrame_Distance4)
        self.progressBar_3.setObjectName(u"progressBar_3")
        self.progressBar_3.setFont(font3)
        self.progressBar_3.setValue(24)

        self.horizontalLayout_18.addWidget(self.progressBar_3)


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
        self.label_UpDownValue = QLabel(self.gridFrame_UpDownValue)
        self.label_UpDownValue.setObjectName(u"label_UpDownValue")
        font4 = QFont()
        font4.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font4.setPointSize(36)
        font4.setBold(True)
        self.label_UpDownValue.setFont(font4)
        self.label_UpDownValue.setAlignment(Qt.AlignCenter)

        self.gridLayout_4.addWidget(self.label_UpDownValue, 1, 0, 1, 1)

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

        self.label_FRValue = QLabel(self.gridFrame_FRValue)
        self.label_FRValue.setObjectName(u"label_FRValue")
        self.label_FRValue.setFont(font4)
        self.label_FRValue.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_FRValue, 1, 0, 1, 1)

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
        self.gridLayoutWidget.setGeometry(QRect(0, 70, 1011, 331))
        self.gridLayout_2 = QGridLayout(self.gridLayoutWidget)
        self.gridLayout_2.setSpacing(1)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
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
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.label_2mm.sizePolicy().hasHeightForWidth())
        self.label_2mm.setSizePolicy(sizePolicy3)
        self.label_2mm.setMinimumSize(QSize(50, 0))
        self.label_2mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_13.addWidget(self.label_2mm)


        self.gridLayout_2.addWidget(self.horizontalFrame_2Value, 3, 2, 1, 1)

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

        self.pushButton_Power = QPushButton(self.gridLayoutWidget)
        self.pushButton_Power.setObjectName(u"pushButton_Power")
        sizePolicy.setHeightForWidth(self.pushButton_Power.sizePolicy().hasHeightForWidth())
        self.pushButton_Power.setSizePolicy(sizePolicy)
        self.pushButton_Power.setMinimumSize(QSize(120, 0))
        font5 = QFont()
        font5.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font5.setPointSize(30)
        font5.setBold(True)
        self.pushButton_Power.setFont(font5)
        self.pushButton_Power.setIconSize(QSize(80, 80))

        self.gridLayout_2.addWidget(self.pushButton_Power, 3, 5, 1, 1)

        self.pushButton_Updown1 = QPushButton(self.gridLayoutWidget)
        self.pushButton_Updown1.setObjectName(u"pushButton_Updown1")
        sizePolicy.setHeightForWidth(self.pushButton_Updown1.sizePolicy().hasHeightForWidth())
        self.pushButton_Updown1.setSizePolicy(sizePolicy)
        self.pushButton_Updown1.setMaximumSize(QSize(180, 16777215))
        self.pushButton_Updown1.setFont(font5)
        self.pushButton_Updown1.setStyleSheet(u"color: rgb(255, 0, 0);")
        self.pushButton_Updown1.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_Updown1, 0, 3, 1, 1)

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
        sizePolicy3.setHeightForWidth(self.label_FR2mm.sizePolicy().hasHeightForWidth())
        self.label_FR2mm.setSizePolicy(sizePolicy3)
        self.label_FR2mm.setMinimumSize(QSize(50, 0))
        font6 = QFont()
        font6.setPointSize(16)
        font6.setBold(True)
        self.label_FR2mm.setFont(font6)
        self.label_FR2mm.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR2mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout_7.addWidget(self.label_FR2mm, 0, 1, 1, 1)

        self.label_FR2Value = QLabel(self.horizontalFrame_2ValueUpDown)
        self.label_FR2Value.setObjectName(u"label_FR2Value")
        self.label_FR2Value.setMinimumSize(QSize(200, 0))
        self.label_FR2Value.setFont(font4)
        self.label_FR2Value.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR2Value.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_FR2Value, 0, 0, 1, 1)


        self.gridLayout_2.addWidget(self.horizontalFrame_2ValueUpDown, 4, 2, 1, 1)

        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.horizontalLayout_6.setContentsMargins(-1, -1, 0, -1)
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
        self.label_10.setAlignment(Qt.AlignBottom|Qt.AlignRight|Qt.AlignTrailing)

        self.gridLayout_5.addWidget(self.label_10, 1, 1, 1, 1)

        self.label_UpDownValue_2 = QLabel(self.gridFrame_UpDownValue_2)
        self.label_UpDownValue_2.setObjectName(u"label_UpDownValue_2")
        self.label_UpDownValue_2.setFont(font4)
        self.label_UpDownValue_2.setAlignment(Qt.AlignCenter)

        self.gridLayout_5.addWidget(self.label_UpDownValue_2, 1, 0, 1, 1)

        self.label_4 = QLabel(self.gridFrame_UpDownValue_2)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setFrameShape(QFrame.Panel)
        self.label_4.setFrameShadow(QFrame.Raised)
        self.label_4.setPixmap(QPixmap(u":/Medical/Picture/arrow up down1.png"))
        self.label_4.setAlignment(Qt.AlignCenter)

        self.gridLayout_5.addWidget(self.label_4, 0, 0, 1, 2)


        self.horizontalLayout_6.addWidget(self.gridFrame_UpDownValue_2)

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

        self.label_FRValue_3 = QLabel(self.gridFrame_FRValue_2)
        self.label_FRValue_3.setObjectName(u"label_FRValue_3")
        self.label_FRValue_3.setFont(font4)
        self.label_FRValue_3.setAlignment(Qt.AlignCenter)

        self.gridLayout_9.addWidget(self.label_FRValue_3, 1, 0, 1, 1)

        self.label_11 = QLabel(self.gridFrame_FRValue_2)
        self.label_11.setObjectName(u"label_11")
        self.label_11.setFrameShape(QFrame.Panel)
        self.label_11.setFrameShadow(QFrame.Raised)
        self.label_11.setPixmap(QPixmap(u":/Medical/Picture/Arrow Right Left 45.png"))
        self.label_11.setAlignment(Qt.AlignCenter)

        self.gridLayout_9.addWidget(self.label_11, 0, 0, 1, 2)


        self.horizontalLayout_6.addWidget(self.gridFrame_FRValue_2)


        self.gridLayout_2.addLayout(self.horizontalLayout_6, 0, 4, 3, 2)

        self.horizontalFrame_1ValueUpDown = QFrame(self.gridLayoutWidget)
        self.horizontalFrame_1ValueUpDown.setObjectName(u"horizontalFrame_1ValueUpDown")
        self.horizontalFrame_1ValueUpDown.setFrameShape(QFrame.Panel)
        self.horizontalFrame_1ValueUpDown.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.horizontalFrame_1ValueUpDown)
        self.horizontalLayout_9.setSpacing(0)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(0, 0, 0, 0)
        self.label_FR1Value = QLabel(self.horizontalFrame_1ValueUpDown)
        self.label_FR1Value.setObjectName(u"label_FR1Value")
        self.label_FR1Value.setMinimumSize(QSize(200, 0))
        self.label_FR1Value.setFont(font4)
        self.label_FR1Value.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR1Value.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_9.addWidget(self.label_FR1Value)

        self.label_FR1mm = QLabel(self.horizontalFrame_1ValueUpDown)
        self.label_FR1mm.setObjectName(u"label_FR1mm")
        sizePolicy3.setHeightForWidth(self.label_FR1mm.sizePolicy().hasHeightForWidth())
        self.label_FR1mm.setSizePolicy(sizePolicy3)
        self.label_FR1mm.setMinimumSize(QSize(50, 0))
        self.label_FR1mm.setFont(font1)
        self.label_FR1mm.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.label_FR1mm.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_9.addWidget(self.label_FR1mm)


        self.gridLayout_2.addWidget(self.horizontalFrame_1ValueUpDown, 2, 2, 1, 1)

        self.horizontalFrame2 = QFrame(self.gridLayoutWidget)
        self.horizontalFrame2.setObjectName(u"horizontalFrame2")
        self.horizontalFrame2.setFrameShape(QFrame.Panel)
        self.horizontalFrame2.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_5 = QHBoxLayout(self.horizontalFrame2)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.label_2IUpDown = QLabel(self.horizontalFrame2)
        self.label_2IUpDown.setObjectName(u"label_2IUpDown")
        sizePolicy3.setHeightForWidth(self.label_2IUpDown.sizePolicy().hasHeightForWidth())
        self.label_2IUpDown.setSizePolicy(sizePolicy3)
        self.label_2IUpDown.setMaximumSize(QSize(60, 16777215))
        self.label_2IUpDown.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_2IUpDown.setScaledContents(True)
        self.label_2IUpDown.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_5.addWidget(self.label_2IUpDown)


        self.gridLayout_2.addWidget(self.horizontalFrame2, 3, 1, 1, 1)

        self.pushButton_FRSet2 = QPushButton(self.gridLayoutWidget)
        self.pushButton_FRSet2.setObjectName(u"pushButton_FRSet2")
        sizePolicy.setHeightForWidth(self.pushButton_FRSet2.sizePolicy().hasHeightForWidth())
        self.pushButton_FRSet2.setSizePolicy(sizePolicy)
        self.pushButton_FRSet2.setMaximumSize(QSize(180, 16777215))
        self.pushButton_FRSet2.setFont(font5)
        self.pushButton_FRSet2.setStyleSheet(u"background-color: rgb(85, 255, 255);\n"
"color: rgb(255, 0, 0);")
        self.pushButton_FRSet2.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_FRSet2, 4, 3, 1, 1)

        self.horizontalFrameDirection = QFrame(self.gridLayoutWidget)
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
        self.pushButton_Up.setAutoRepeat(True)
        self.pushButton_Up.setAutoRepeatInterval(50)

        self.horizontalLayout.addWidget(self.pushButton_Up)

        self.pushButton_Down = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Down.setObjectName(u"pushButton_Down")
        icon1 = QIcon()
        icon1.addFile(u":/Medical/Picture/down arrow.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Down.setIcon(icon1)
        self.pushButton_Down.setIconSize(QSize(80, 80))
        self.pushButton_Down.setAutoRepeat(True)
        self.pushButton_Down.setAutoRepeatInterval(50)

        self.horizontalLayout.addWidget(self.pushButton_Down)

        self.pushButton_Front = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Front.setObjectName(u"pushButton_Front")
        self.pushButton_Front.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon2 = QIcon()
        icon2.addFile(u":/Medical/Picture/Arrow Leftt45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Front.setIcon(icon2)
        self.pushButton_Front.setIconSize(QSize(80, 80))
        self.pushButton_Front.setAutoRepeat(True)
        self.pushButton_Front.setAutoRepeatInterval(50)

        self.horizontalLayout.addWidget(self.pushButton_Front)

        self.pushButton_Rear = QPushButton(self.horizontalFrameDirection)
        self.pushButton_Rear.setObjectName(u"pushButton_Rear")
        self.pushButton_Rear.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon3 = QIcon()
        icon3.addFile(u":/Medical/Picture/Arrow Right45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Rear.setIcon(icon3)
        self.pushButton_Rear.setIconSize(QSize(80, 80))
        self.pushButton_Rear.setAutoRepeat(True)
        self.pushButton_Rear.setAutoRepeatInterval(50)

        self.horizontalLayout.addWidget(self.pushButton_Rear)


        self.gridLayout_2.addWidget(self.horizontalFrameDirection, 3, 4, 1, 1)

        self.label_2Label = QLabel(self.gridLayoutWidget)
        self.label_2Label.setObjectName(u"label_2Label")
        self.label_2Label.setFont(font5)
        self.label_2Label.setFrameShape(QFrame.Panel)
        self.label_2Label.setFrameShadow(QFrame.Raised)
        self.label_2Label.setAlignment(Qt.AlignCenter)

        self.gridLayout_2.addWidget(self.label_2Label, 3, 0, 2, 1)

        self.pushButton_FR_2 = QPushButton(self.gridLayoutWidget)
        self.pushButton_FR_2.setObjectName(u"pushButton_FR_2")
        sizePolicy4 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.pushButton_FR_2.sizePolicy().hasHeightForWidth())
        self.pushButton_FR_2.setSizePolicy(sizePolicy4)
        self.pushButton_FR_2.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        icon4 = QIcon()
        icon4.addFile(u":/Medical/Picture/Arrow Double.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_FR_2.setIcon(icon4)
        self.pushButton_FR_2.setIconSize(QSize(70, 70))

        self.gridLayout_2.addWidget(self.pushButton_FR_2, 4, 1, 1, 1)

        self.pushButton_FR = QPushButton(self.gridLayoutWidget)
        self.pushButton_FR.setObjectName(u"pushButton_FR")
        sizePolicy4.setHeightForWidth(self.pushButton_FR.sizePolicy().hasHeightForWidth())
        self.pushButton_FR.setSizePolicy(sizePolicy4)
        self.pushButton_FR.setStyleSheet(u"background-color: rgb(85, 255, 255);")
        self.pushButton_FR.setIcon(icon4)
        self.pushButton_FR.setIconSize(QSize(70, 70))

        self.gridLayout_2.addWidget(self.pushButton_FR, 2, 1, 1, 1)

        self.pushButton_Updown2 = QPushButton(self.gridLayoutWidget)
        self.pushButton_Updown2.setObjectName(u"pushButton_Updown2")
        sizePolicy.setHeightForWidth(self.pushButton_Updown2.sizePolicy().hasHeightForWidth())
        self.pushButton_Updown2.setSizePolicy(sizePolicy)
        self.pushButton_Updown2.setMaximumSize(QSize(180, 16777215))
        self.pushButton_Updown2.setFont(font5)
        self.pushButton_Updown2.setStyleSheet(u"color: rgb(255, 0, 0);")
        self.pushButton_Updown2.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_Updown2, 3, 3, 1, 1)

        self.label_1Label = QLabel(self.gridLayoutWidget)
        self.label_1Label.setObjectName(u"label_1Label")
        self.label_1Label.setFont(font5)
        self.label_1Label.setFrameShape(QFrame.Panel)
        self.label_1Label.setFrameShadow(QFrame.Raised)
        self.label_1Label.setAlignment(Qt.AlignCenter)

        self.gridLayout_2.addWidget(self.label_1Label, 0, 0, 3, 1)

        self.pushButton_FRSet1 = QPushButton(self.gridLayoutWidget)
        self.pushButton_FRSet1.setObjectName(u"pushButton_FRSet1")
        sizePolicy.setHeightForWidth(self.pushButton_FRSet1.sizePolicy().hasHeightForWidth())
        self.pushButton_FRSet1.setSizePolicy(sizePolicy)
        self.pushButton_FRSet1.setMaximumSize(QSize(180, 16777215))
        self.pushButton_FRSet1.setFont(font5)
        self.pushButton_FRSet1.setStyleSheet(u"background-color: rgb(85, 255, 255);\n"
"color: rgb(255, 0, 0);")
        self.pushButton_FRSet1.setIconSize(QSize(60, 60))

        self.gridLayout_2.addWidget(self.pushButton_FRSet1, 2, 3, 1, 1)

        self.horizontalFrame_1 = QFrame(self.gridLayoutWidget)
        self.horizontalFrame_1.setObjectName(u"horizontalFrame_1")
        self.horizontalFrame_1.setFrameShape(QFrame.Panel)
        self.horizontalFrame_1.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_3 = QHBoxLayout(self.horizontalFrame_1)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.label_1IUpDown = QLabel(self.horizontalFrame_1)
        self.label_1IUpDown.setObjectName(u"label_1IUpDown")
        sizePolicy3.setHeightForWidth(self.label_1IUpDown.sizePolicy().hasHeightForWidth())
        self.label_1IUpDown.setSizePolicy(sizePolicy3)
        self.label_1IUpDown.setMaximumSize(QSize(60, 16777215))
        self.label_1IUpDown.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_1IUpDown.setScaledContents(True)
        self.label_1IUpDown.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_3.addWidget(self.label_1IUpDown)


        self.gridLayout_2.addWidget(self.horizontalFrame_1, 0, 1, 1, 1)

        self.horizontalLayout_10 = QHBoxLayout()
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.pushButton_Zero = QPushButton(self.gridLayoutWidget)
        self.pushButton_Zero.setObjectName(u"pushButton_Zero")
        sizePolicy.setHeightForWidth(self.pushButton_Zero.sizePolicy().hasHeightForWidth())
        self.pushButton_Zero.setSizePolicy(sizePolicy)
        font7 = QFont()
        font7.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font7.setPointSize(22)
        font7.setBold(True)
        self.pushButton_Zero.setFont(font7)
        self.pushButton_Zero.setIconSize(QSize(60, 60))

        self.horizontalLayout_10.addWidget(self.pushButton_Zero)

        self.pushButton_Reset = QPushButton(self.gridLayoutWidget)
        self.pushButton_Reset.setObjectName(u"pushButton_Reset")
        sizePolicy.setHeightForWidth(self.pushButton_Reset.sizePolicy().hasHeightForWidth())
        self.pushButton_Reset.setSizePolicy(sizePolicy)
        self.pushButton_Reset.setMinimumSize(QSize(0, 70))
        self.pushButton_Reset.setFont(font7)
        self.pushButton_Reset.setIconSize(QSize(60, 60))

        self.horizontalLayout_10.addWidget(self.pushButton_Reset)

        self.horizontalLayout_10.setStretch(0, 2)
        self.horizontalLayout_10.setStretch(1, 3)

        self.gridLayout_2.addLayout(self.horizontalLayout_10, 4, 4, 1, 2)

        self.horizontalLayoutWidget_2 = QWidget(self.tab_Paramter)
        self.horizontalLayoutWidget_2.setObjectName(u"horizontalLayoutWidget_2")
        self.horizontalLayoutWidget_2.setGeometry(QRect(10, 0, 468, 61))
        self.horizontalLayout_7 = QHBoxLayout(self.horizontalLayoutWidget_2)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.radioButton_English = QRadioButton(self.horizontalLayoutWidget_2)
        self.radioButton_English.setObjectName(u"radioButton_English")
        self.radioButton_English.setMaximumSize(QSize(200, 40))
        font8 = QFont()
        font8.setFamilies([u"Arial"])
        font8.setPointSize(18)
        font8.setBold(True)
        self.radioButton_English.setFont(font8)
        self.radioButton_English.setCheckable(True)

        self.horizontalLayout_7.addWidget(self.radioButton_English)

        self.radioButton_Chinese = QRadioButton(self.horizontalLayoutWidget_2)
        self.radioButton_Chinese.setObjectName(u"radioButton_Chinese")
        self.radioButton_Chinese.setMaximumSize(QSize(200, 40))
        self.radioButton_Chinese.setFont(font8)
        self.radioButton_Chinese.setCheckable(True)

        self.horizontalLayout_7.addWidget(self.radioButton_Chinese)

        self.radioButton_Simplified = QRadioButton(self.horizontalLayoutWidget_2)
        self.radioButton_Simplified.setObjectName(u"radioButton_Simplified")
        self.radioButton_Simplified.setMaximumSize(QSize(200, 40))
        self.radioButton_Simplified.setFont(font8)
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
        self.progressBar.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_LoadLable2.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf2", None))
        self.progressBar_2.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_LoadLable3.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf3", None))
        self.progressBar_4.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_LoadLable4.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u91cf4", None))
        self.progressBar_3.setFormat(QCoreApplication.translate("MainWindow", u"%pg", None))
        self.label_UpDownValue.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_3.setText("")
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FRValue.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.label_2.setText("")
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Run), QCoreApplication.translate("MainWindow", u"\u57f7\u884c", None))
        self.label_Updown2.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_2mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_Updown1.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_1mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_Power.setText(QCoreApplication.translate("MainWindow", u"X1", None))
        self.pushButton_Updown1.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_FR2mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FR2Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_UpDownValue_2.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.label_4.setText("")
        self.label_8.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_FRValue_3.setText(QCoreApplication.translate("MainWindow", u"000", None))
        self.label_11.setText("")
        self.label_FR1Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_FR1mm.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_2IUpDown.setText("")
        self.pushButton_FRSet2.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.pushButton_Up.setText("")
        self.pushButton_Down.setText("")
        self.pushButton_Front.setText("")
        self.pushButton_Rear.setText("")
        self.label_2Label.setText(QCoreApplication.translate("MainWindow", u"2", None))
        self.pushButton_FR_2.setText("")
        self.pushButton_FR.setText("")
        self.pushButton_Updown2.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_1Label.setText(QCoreApplication.translate("MainWindow", u"1", None))
        self.pushButton_FRSet1.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_1IUpDown.setText("")
        self.pushButton_Zero.setText(QCoreApplication.translate("MainWindow", u"\u6b78\u96f6", None))
        self.pushButton_Reset.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u7f6e", None))
        self.radioButton_English.setText(QCoreApplication.translate("MainWindow", u"English", None))
        self.radioButton_Chinese.setText(QCoreApplication.translate("MainWindow", u"\u7e41\u9ad4", None))
        self.radioButton_Simplified.setText(QCoreApplication.translate("MainWindow", u"\u7b80\u4f53", None))
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Paramter), QCoreApplication.translate("MainWindow", u"\u53c3\u6578", None))
    # retranslateUi


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
    QSizePolicy, QTabWidget, QVBoxLayout, QWidget)
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
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(-1, -1, -1, 0)
        self.gridFrame_2 = QFrame(self.horizontalFrame_2)
        self.gridFrame_2.setObjectName(u"gridFrame_2")
        self.gridFrame_2.setFrameShape(QFrame.Panel)
        self.gridLayout_2 = QGridLayout(self.gridFrame_2)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.progressBar = QProgressBar(self.gridFrame_2)
        self.progressBar.setObjectName(u"progressBar")
        self.progressBar.setValue(24)

        self.gridLayout_2.addWidget(self.progressBar, 1, 0, 1, 3)

        self.label = QLabel(self.gridFrame_2)
        self.label.setObjectName(u"label")

        self.gridLayout_2.addWidget(self.label, 0, 0, 1, 1)

        self.label_3 = QLabel(self.gridFrame_2)
        self.label_3.setObjectName(u"label_3")

        self.gridLayout_2.addWidget(self.label_3, 0, 2, 1, 1)

        self.label_2 = QLabel(self.gridFrame_2)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout_2.addWidget(self.label_2, 0, 1, 1, 1)


        self.verticalLayout_2.addWidget(self.gridFrame_2)

        self.gridFrame_3 = QFrame(self.horizontalFrame_2)
        self.gridFrame_3.setObjectName(u"gridFrame_3")
        self.gridFrame_3.setFrameShape(QFrame.Panel)
        self.gridLayout_3 = QGridLayout(self.gridFrame_3)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.label_4 = QLabel(self.gridFrame_3)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout_3.addWidget(self.label_4, 0, 1, 1, 1)

        self.label_5 = QLabel(self.gridFrame_3)
        self.label_5.setObjectName(u"label_5")

        self.gridLayout_3.addWidget(self.label_5, 0, 0, 1, 1)

        self.label_6 = QLabel(self.gridFrame_3)
        self.label_6.setObjectName(u"label_6")

        self.gridLayout_3.addWidget(self.label_6, 0, 2, 1, 1)

        self.progressBar_2 = QProgressBar(self.gridFrame_3)
        self.progressBar_2.setObjectName(u"progressBar_2")
        self.progressBar_2.setValue(24)

        self.gridLayout_3.addWidget(self.progressBar_2, 1, 0, 1, 3)


        self.verticalLayout_2.addWidget(self.gridFrame_3)

        self.gridFrame_4 = QFrame(self.horizontalFrame_2)
        self.gridFrame_4.setObjectName(u"gridFrame_4")
        self.gridFrame_4.setFrameShape(QFrame.Panel)
        self.gridLayout_4 = QGridLayout(self.gridFrame_4)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.label_7 = QLabel(self.gridFrame_4)
        self.label_7.setObjectName(u"label_7")

        self.gridLayout_4.addWidget(self.label_7, 0, 1, 1, 1)

        self.label_8 = QLabel(self.gridFrame_4)
        self.label_8.setObjectName(u"label_8")

        self.gridLayout_4.addWidget(self.label_8, 0, 0, 1, 1)

        self.label_9 = QLabel(self.gridFrame_4)
        self.label_9.setObjectName(u"label_9")

        self.gridLayout_4.addWidget(self.label_9, 0, 2, 1, 1)

        self.progressBar_3 = QProgressBar(self.gridFrame_4)
        self.progressBar_3.setObjectName(u"progressBar_3")
        self.progressBar_3.setValue(24)

        self.gridLayout_4.addWidget(self.progressBar_3, 1, 0, 1, 3)


        self.verticalLayout_2.addWidget(self.gridFrame_4)

        self.gridFrame_5 = QFrame(self.horizontalFrame_2)
        self.gridFrame_5.setObjectName(u"gridFrame_5")
        self.gridFrame_5.setFrameShape(QFrame.Panel)
        self.gridLayout_5 = QGridLayout(self.gridFrame_5)
        self.gridLayout_5.setObjectName(u"gridLayout_5")
        self.label_10 = QLabel(self.gridFrame_5)
        self.label_10.setObjectName(u"label_10")

        self.gridLayout_5.addWidget(self.label_10, 0, 1, 1, 1)

        self.label_11 = QLabel(self.gridFrame_5)
        self.label_11.setObjectName(u"label_11")

        self.gridLayout_5.addWidget(self.label_11, 0, 0, 1, 1)

        self.label_12 = QLabel(self.gridFrame_5)
        self.label_12.setObjectName(u"label_12")

        self.gridLayout_5.addWidget(self.label_12, 0, 2, 1, 1)

        self.progressBar_4 = QProgressBar(self.gridFrame_5)
        self.progressBar_4.setObjectName(u"progressBar_4")
        self.progressBar_4.setValue(24)

        self.gridLayout_5.addWidget(self.progressBar_4, 1, 0, 1, 3)


        self.verticalLayout_2.addWidget(self.gridFrame_5)


        self.gridLayout_6.addLayout(self.verticalLayout_2, 0, 1, 1, 1)

        self.verticalLayout = QVBoxLayout()
        self.verticalLayout.setSpacing(4)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(-1, -1, -1, 0)
        self.horizontalFrame11 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame11.setObjectName(u"horizontalFrame11")
        self.horizontalFrame11.setFrameShape(QFrame.Panel)
        self.horizontalFrame11.setLineWidth(1)
        self.horizontalLayout = QHBoxLayout(self.horizontalFrame11)
        self.horizontalLayout.setSpacing(2)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.pushButton_Up = QPushButton(self.horizontalFrame11)
        self.pushButton_Up.setObjectName(u"pushButton_Up")
        icon = QIcon()
        icon.addFile(u":/Medical/Picture/up arrow.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Up.setIcon(icon)
        self.pushButton_Up.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Up)

        self.pushButton_Down = QPushButton(self.horizontalFrame11)
        self.pushButton_Down.setObjectName(u"pushButton_Down")
        icon1 = QIcon()
        icon1.addFile(u":/Medical/Picture/down arrow.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Down.setIcon(icon1)
        self.pushButton_Down.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Down)

        self.pushButton_Front = QPushButton(self.horizontalFrame11)
        self.pushButton_Front.setObjectName(u"pushButton_Front")
        self.pushButton_Front.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        icon2 = QIcon()
        icon2.addFile(u":/Medical/Picture/Arrow Leftt45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Front.setIcon(icon2)
        self.pushButton_Front.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Front)

        self.pushButton_Rear = QPushButton(self.horizontalFrame11)
        self.pushButton_Rear.setObjectName(u"pushButton_Rear")
        self.pushButton_Rear.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        icon3 = QIcon()
        icon3.addFile(u":/Medical/Picture/Arrow Right45.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_Rear.setIcon(icon3)
        self.pushButton_Rear.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Rear)

        self.pushButton_Power = QPushButton(self.horizontalFrame11)
        self.pushButton_Power.setObjectName(u"pushButton_Power")
        sizePolicy.setHeightForWidth(self.pushButton_Power.sizePolicy().hasHeightForWidth())
        self.pushButton_Power.setSizePolicy(sizePolicy)
        font2 = QFont()
        font2.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font2.setPointSize(22)
        font2.setBold(True)
        self.pushButton_Power.setFont(font2)
        self.pushButton_Power.setIconSize(QSize(80, 80))

        self.horizontalLayout.addWidget(self.pushButton_Power)

        self.horizontalLayout.setStretch(0, 1)
        self.horizontalLayout.setStretch(1, 1)
        self.horizontalLayout.setStretch(2, 1)
        self.horizontalLayout.setStretch(3, 1)
        self.horizontalLayout.setStretch(4, 1)

        self.verticalLayout.addWidget(self.horizontalFrame11)

        self.horizontalFrame12 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame12.setObjectName(u"horizontalFrame12")
        sizePolicy.setHeightForWidth(self.horizontalFrame12.sizePolicy().hasHeightForWidth())
        self.horizontalFrame12.setSizePolicy(sizePolicy)
        self.horizontalFrame12.setFrameShape(QFrame.Panel)
        self.horizontalFrame12.setFrameShadow(QFrame.Plain)
        self.horizontalFrame12.setLineWidth(1)
        self.horizontalLayout_4 = QHBoxLayout(self.horizontalFrame12)
        self.horizontalLayout_4.setSpacing(1)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.horizontalFrame = QFrame(self.horizontalFrame12)
        self.horizontalFrame.setObjectName(u"horizontalFrame")
        self.horizontalFrame.setFrameShape(QFrame.Panel)
        self.horizontalFrame.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_8 = QHBoxLayout(self.horizontalFrame)
        self.horizontalLayout_8.setSpacing(0)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.horizontalLayout_8.setContentsMargins(0, 0, 4, 0)
        self.label_13 = QLabel(self.horizontalFrame)
        self.label_13.setObjectName(u"label_13")
        sizePolicy.setHeightForWidth(self.label_13.sizePolicy().hasHeightForWidth())
        self.label_13.setSizePolicy(sizePolicy)
        self.label_13.setFont(font2)
        self.label_13.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_8.addWidget(self.label_13)

        self.label_16 = QLabel(self.horizontalFrame)
        self.label_16.setObjectName(u"label_16")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.label_16.sizePolicy().hasHeightForWidth())
        self.label_16.setSizePolicy(sizePolicy2)
        self.label_16.setMaximumSize(QSize(60, 16777215))
        self.label_16.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_16.setScaledContents(True)

        self.horizontalLayout_8.addWidget(self.label_16)


        self.horizontalLayout_4.addWidget(self.horizontalFrame)

        self.horizontalFrame_21 = QFrame(self.horizontalFrame12)
        self.horizontalFrame_21.setObjectName(u"horizontalFrame_21")
        self.horizontalFrame_21.setFrameShape(QFrame.Panel)
        self.horizontalFrame_21.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.horizontalFrame_21)
        self.horizontalLayout_9.setSpacing(0)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(-1, -1, 1, -1)
        self.label_15 = QLabel(self.horizontalFrame_21)
        self.label_15.setObjectName(u"label_15")
        sizePolicy.setHeightForWidth(self.label_15.sizePolicy().hasHeightForWidth())
        self.label_15.setSizePolicy(sizePolicy)
        font3 = QFont()
        font3.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font3.setPointSize(36)
        font3.setBold(True)
        self.label_15.setFont(font3)
        self.label_15.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_9.addWidget(self.label_15)

        self.label_17 = QLabel(self.horizontalFrame_21)
        self.label_17.setObjectName(u"label_17")
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Expanding)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.label_17.sizePolicy().hasHeightForWidth())
        self.label_17.setSizePolicy(sizePolicy3)
        self.label_17.setMinimumSize(QSize(50, 0))
        self.label_17.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_9.addWidget(self.label_17)


        self.horizontalLayout_4.addWidget(self.horizontalFrame_21)

        self.pushButton_StartSet = QPushButton(self.horizontalFrame12)
        self.pushButton_StartSet.setObjectName(u"pushButton_StartSet")
        sizePolicy.setHeightForWidth(self.pushButton_StartSet.sizePolicy().hasHeightForWidth())
        self.pushButton_StartSet.setSizePolicy(sizePolicy)
        self.pushButton_StartSet.setFont(font2)
        self.pushButton_StartSet.setIconSize(QSize(60, 60))

        self.horizontalLayout_4.addWidget(self.pushButton_StartSet)

        self.horizontalLayout_4.setStretch(0, 1)
        self.horizontalLayout_4.setStretch(1, 2)
        self.horizontalLayout_4.setStretch(2, 1)

        self.verticalLayout.addWidget(self.horizontalFrame12)

        self.horizontalFrame_13 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame_13.setObjectName(u"horizontalFrame_13")
        self.horizontalFrame_13.setFrameShape(QFrame.Panel)
        self.horizontalLayout_5 = QHBoxLayout(self.horizontalFrame_13)
        self.horizontalLayout_5.setSpacing(2)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.horizontalFrame_3 = QFrame(self.horizontalFrame_13)
        self.horizontalFrame_3.setObjectName(u"horizontalFrame_3")
        self.horizontalFrame_3.setFrameShape(QFrame.Panel)
        self.horizontalFrame_3.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_10 = QHBoxLayout(self.horizontalFrame_3)
        self.horizontalLayout_10.setSpacing(0)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.horizontalLayout_10.setContentsMargins(0, 0, 4, 0)
        self.label_1 = QLabel(self.horizontalFrame_3)
        self.label_1.setObjectName(u"label_1")
        font4 = QFont()
        font4.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font4.setPointSize(30)
        font4.setBold(True)
        self.label_1.setFont(font4)
        self.label_1.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_10.addWidget(self.label_1)

        self.label_18 = QLabel(self.horizontalFrame_3)
        self.label_18.setObjectName(u"label_18")
        sizePolicy2.setHeightForWidth(self.label_18.sizePolicy().hasHeightForWidth())
        self.label_18.setSizePolicy(sizePolicy2)
        self.label_18.setMaximumSize(QSize(60, 16777215))
        self.label_18.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_18.setScaledContents(True)

        self.horizontalLayout_10.addWidget(self.label_18)


        self.horizontalLayout_5.addWidget(self.horizontalFrame_3)

        self.horizontalFrame_4 = QFrame(self.horizontalFrame_13)
        self.horizontalFrame_4.setObjectName(u"horizontalFrame_4")
        self.horizontalFrame_4.setFrameShape(QFrame.Panel)
        self.horizontalFrame_4.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_11 = QHBoxLayout(self.horizontalFrame_4)
        self.horizontalLayout_11.setSpacing(0)
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.horizontalLayout_11.setContentsMargins(-1, -1, 1, -1)
        self.label_1Value = QLabel(self.horizontalFrame_4)
        self.label_1Value.setObjectName(u"label_1Value")
        self.label_1Value.setFont(font3)
        self.label_1Value.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_11.addWidget(self.label_1Value)

        self.label_19 = QLabel(self.horizontalFrame_4)
        self.label_19.setObjectName(u"label_19")
        sizePolicy2.setHeightForWidth(self.label_19.sizePolicy().hasHeightForWidth())
        self.label_19.setSizePolicy(sizePolicy2)
        self.label_19.setMinimumSize(QSize(50, 0))
        self.label_19.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_11.addWidget(self.label_19)


        self.horizontalLayout_5.addWidget(self.horizontalFrame_4)

        self.pushButton_1Set = QPushButton(self.horizontalFrame_13)
        self.pushButton_1Set.setObjectName(u"pushButton_1Set")
        sizePolicy.setHeightForWidth(self.pushButton_1Set.sizePolicy().hasHeightForWidth())
        self.pushButton_1Set.setSizePolicy(sizePolicy)
        self.pushButton_1Set.setFont(font2)
        self.pushButton_1Set.setIconSize(QSize(60, 60))

        self.horizontalLayout_5.addWidget(self.pushButton_1Set)

        self.horizontalLayout_5.setStretch(0, 1)
        self.horizontalLayout_5.setStretch(1, 2)
        self.horizontalLayout_5.setStretch(2, 1)

        self.verticalLayout.addWidget(self.horizontalFrame_13)

        self.horizontalFrame14 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame14.setObjectName(u"horizontalFrame14")
        self.horizontalFrame14.setFrameShape(QFrame.Panel)
        self.horizontalLayout_6 = QHBoxLayout(self.horizontalFrame14)
        self.horizontalLayout_6.setSpacing(2)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.horizontalFrame_5 = QFrame(self.horizontalFrame14)
        self.horizontalFrame_5.setObjectName(u"horizontalFrame_5")
        self.horizontalFrame_5.setFrameShape(QFrame.Panel)
        self.horizontalFrame_5.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_12 = QHBoxLayout(self.horizontalFrame_5)
        self.horizontalLayout_12.setSpacing(0)
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.horizontalLayout_12.setContentsMargins(0, 0, 4, 0)
        self.label_14 = QLabel(self.horizontalFrame_5)
        self.label_14.setObjectName(u"label_14")
        self.label_14.setFont(font4)
        self.label_14.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_12.addWidget(self.label_14)

        self.label_20 = QLabel(self.horizontalFrame_5)
        self.label_20.setObjectName(u"label_20")
        sizePolicy2.setHeightForWidth(self.label_20.sizePolicy().hasHeightForWidth())
        self.label_20.setSizePolicy(sizePolicy2)
        self.label_20.setMaximumSize(QSize(60, 16777215))
        self.label_20.setPixmap(QPixmap(u":/Medical/Picture/arrow up down.png"))
        self.label_20.setScaledContents(True)

        self.horizontalLayout_12.addWidget(self.label_20)


        self.horizontalLayout_6.addWidget(self.horizontalFrame_5)

        self.horizontalFrame_6 = QFrame(self.horizontalFrame14)
        self.horizontalFrame_6.setObjectName(u"horizontalFrame_6")
        self.horizontalFrame_6.setFrameShape(QFrame.Panel)
        self.horizontalFrame_6.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_13 = QHBoxLayout(self.horizontalFrame_6)
        self.horizontalLayout_13.setSpacing(0)
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.horizontalLayout_13.setContentsMargins(-1, -1, 1, -1)
        self.label_2Value = QLabel(self.horizontalFrame_6)
        self.label_2Value.setObjectName(u"label_2Value")
        self.label_2Value.setFont(font3)
        self.label_2Value.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_13.addWidget(self.label_2Value)

        self.label_21 = QLabel(self.horizontalFrame_6)
        self.label_21.setObjectName(u"label_21")
        sizePolicy2.setHeightForWidth(self.label_21.sizePolicy().hasHeightForWidth())
        self.label_21.setSizePolicy(sizePolicy2)
        self.label_21.setMinimumSize(QSize(50, 0))
        self.label_21.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.horizontalLayout_13.addWidget(self.label_21)


        self.horizontalLayout_6.addWidget(self.horizontalFrame_6)

        self.pushButton_2Set = QPushButton(self.horizontalFrame14)
        self.pushButton_2Set.setObjectName(u"pushButton_2Set")
        sizePolicy.setHeightForWidth(self.pushButton_2Set.sizePolicy().hasHeightForWidth())
        self.pushButton_2Set.setSizePolicy(sizePolicy)
        self.pushButton_2Set.setFont(font2)
        self.pushButton_2Set.setIconSize(QSize(60, 60))

        self.horizontalLayout_6.addWidget(self.pushButton_2Set)

        self.horizontalLayout_6.setStretch(0, 1)
        self.horizontalLayout_6.setStretch(1, 2)
        self.horizontalLayout_6.setStretch(2, 1)

        self.verticalLayout.addWidget(self.horizontalFrame14)

        self.horizontalFrame15 = QFrame(self.horizontalFrame_2)
        self.horizontalFrame15.setObjectName(u"horizontalFrame15")
        self.horizontalFrame15.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.horizontalFrame15.setFrameShape(QFrame.Panel)
        self.horizontalLayout_7 = QHBoxLayout(self.horizontalFrame15)
        self.horizontalLayout_7.setSpacing(2)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.pushButton_FrontRear = QPushButton(self.horizontalFrame15)
        self.pushButton_FrontRear.setObjectName(u"pushButton_FrontRear")
        sizePolicy.setHeightForWidth(self.pushButton_FrontRear.sizePolicy().hasHeightForWidth())
        self.pushButton_FrontRear.setSizePolicy(sizePolicy)
        self.pushButton_FrontRear.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        icon4 = QIcon()
        icon4.addFile(u":/Medical/Picture/Arrow Double.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.pushButton_FrontRear.setIcon(icon4)
        self.pushButton_FrontRear.setIconSize(QSize(70, 70))

        self.horizontalLayout_7.addWidget(self.pushButton_FrontRear)

        self.gridFrame = QFrame(self.horizontalFrame15)
        self.gridFrame.setObjectName(u"gridFrame")
        self.gridFrame.setFrameShape(QFrame.Panel)
        self.gridFrame.setFrameShadow(QFrame.Raised)
        self.gridFrame.setLineWidth(1)
        self.gridLayout = QGridLayout(self.gridFrame)
        self.gridLayout.setSpacing(0)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.label_23 = QLabel(self.gridFrame)
        self.label_23.setObjectName(u"label_23")
        sizePolicy2.setHeightForWidth(self.label_23.sizePolicy().hasHeightForWidth())
        self.label_23.setSizePolicy(sizePolicy2)
        font5 = QFont()
        font5.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font5.setPointSize(12)
        font5.setBold(True)
        self.label_23.setFont(font5)
        self.label_23.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_23.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout.addWidget(self.label_23, 1, 1, 1, 1)

        self.label_22 = QLabel(self.gridFrame)
        self.label_22.setObjectName(u"label_22")
        font6 = QFont()
        font6.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font6.setPointSize(24)
        font6.setBold(True)
        self.label_22.setFont(font6)
        self.label_22.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_22.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_22, 1, 0, 1, 1)

        self.label_26 = QLabel(self.gridFrame)
        self.label_26.setObjectName(u"label_26")
        sizePolicy4 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Fixed)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.label_26.sizePolicy().hasHeightForWidth())
        self.label_26.setSizePolicy(sizePolicy4)
        self.label_26.setMaximumSize(QSize(16777215, 26))
        font7 = QFont()
        font7.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font7.setPointSize(20)
        font7.setBold(True)
        self.label_26.setFont(font7)
        self.label_26.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_26.setFrameShape(QFrame.StyledPanel)
        self.label_26.setScaledContents(True)
        self.label_26.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_26, 0, 0, 1, 2)


        self.horizontalLayout_7.addWidget(self.gridFrame)

        self.gridFrame_21 = QFrame(self.horizontalFrame15)
        self.gridFrame_21.setObjectName(u"gridFrame_21")
        self.gridFrame_21.setFrameShape(QFrame.Panel)
        self.gridFrame_21.setFrameShadow(QFrame.Raised)
        self.gridFrame_21.setLineWidth(1)
        self.gridLayout_7 = QGridLayout(self.gridFrame_21)
        self.gridLayout_7.setSpacing(0)
        self.gridLayout_7.setObjectName(u"gridLayout_7")
        self.gridLayout_7.setContentsMargins(0, 0, 0, 0)
        self.label_25 = QLabel(self.gridFrame_21)
        self.label_25.setObjectName(u"label_25")
        sizePolicy2.setHeightForWidth(self.label_25.sizePolicy().hasHeightForWidth())
        self.label_25.setSizePolicy(sizePolicy2)
        self.label_25.setFont(font5)
        self.label_25.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_25.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout_7.addWidget(self.label_25, 1, 1, 1, 1)

        self.label_24 = QLabel(self.gridFrame_21)
        self.label_24.setObjectName(u"label_24")
        self.label_24.setFont(font6)
        self.label_24.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_24.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_24, 1, 0, 1, 1)

        self.label_27 = QLabel(self.gridFrame_21)
        self.label_27.setObjectName(u"label_27")
        sizePolicy4.setHeightForWidth(self.label_27.sizePolicy().hasHeightForWidth())
        self.label_27.setSizePolicy(sizePolicy4)
        self.label_27.setMaximumSize(QSize(16777215, 26))
        self.label_27.setFont(font7)
        self.label_27.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_27.setFrameShape(QFrame.StyledPanel)
        self.label_27.setFrameShadow(QFrame.Plain)
        self.label_27.setScaledContents(True)
        self.label_27.setAlignment(Qt.AlignCenter)

        self.gridLayout_7.addWidget(self.label_27, 0, 0, 1, 2)


        self.horizontalLayout_7.addWidget(self.gridFrame_21)

        self.pushButton_FrontRearSet = QPushButton(self.horizontalFrame15)
        self.pushButton_FrontRearSet.setObjectName(u"pushButton_FrontRearSet")
        sizePolicy.setHeightForWidth(self.pushButton_FrontRearSet.sizePolicy().hasHeightForWidth())
        self.pushButton_FrontRearSet.setSizePolicy(sizePolicy)
        self.pushButton_FrontRearSet.setFont(font2)
        self.pushButton_FrontRearSet.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.pushButton_FrontRearSet.setIconSize(QSize(60, 60))

        self.horizontalLayout_7.addWidget(self.pushButton_FrontRearSet)

        self.horizontalLayout_7.setStretch(0, 1)
        self.horizontalLayout_7.setStretch(1, 1)
        self.horizontalLayout_7.setStretch(2, 1)
        self.horizontalLayout_7.setStretch(3, 1)

        self.verticalLayout.addWidget(self.horizontalFrame15)

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
        self.pushButton_Zero.setFont(font2)
        self.pushButton_Zero.setIconSize(QSize(60, 60))

        self.horizontalLayout_3.addWidget(self.pushButton_Zero)

        self.pushButton_Reset = QPushButton(self.horizontalFrame16)
        self.pushButton_Reset.setObjectName(u"pushButton_Reset")
        sizePolicy.setHeightForWidth(self.pushButton_Reset.sizePolicy().hasHeightForWidth())
        self.pushButton_Reset.setSizePolicy(sizePolicy)
        self.pushButton_Reset.setFont(font2)
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
        self.tabWidget_Main.addTab(self.tab_Paramter, "")

        self.horizontalLayout_2.addWidget(self.tabWidget_Main)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)

        self.tabWidget_Main.setCurrentIndex(0)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"XINDA SERVO SYSTEM", None))
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
        self.label_13.setText(QCoreApplication.translate("MainWindow", u"\u8d77\u59cb", None))
        self.label_16.setText("")
        self.label_15.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_17.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_StartSet.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_1.setText(QCoreApplication.translate("MainWindow", u"1", None))
        self.label_18.setText("")
        self.label_1Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_19.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_1Set.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.label_14.setText(QCoreApplication.translate("MainWindow", u"2", None))
        self.label_20.setText("")
        self.label_2Value.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_21.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.pushButton_2Set.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.pushButton_FrontRear.setText("")
        self.label_23.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_22.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_26.setText(QCoreApplication.translate("MainWindow", u"1", None))
        self.label_25.setText(QCoreApplication.translate("MainWindow", u"mm", None))
        self.label_24.setText(QCoreApplication.translate("MainWindow", u"999", None))
        self.label_27.setText(QCoreApplication.translate("MainWindow", u"2", None))
        self.pushButton_FrontRearSet.setText(QCoreApplication.translate("MainWindow", u"\u8a2d\u5b9a", None))
        self.pushButton_Zero.setText(QCoreApplication.translate("MainWindow", u"\u6b78\u96f6", None))
        self.pushButton_Reset.setText(QCoreApplication.translate("MainWindow", u"\u91cd\u7f6e", None))
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Run), QCoreApplication.translate("MainWindow", u"\u57f7\u884c", None))
        self.tabWidget_Main.setTabText(self.tabWidget_Main.indexOf(self.tab_Paramter), QCoreApplication.translate("MainWindow", u"\u53c3\u6578", None))
    # retranslateUi


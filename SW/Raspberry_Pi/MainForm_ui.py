# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'd:\621\SW_Test\MainForm.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.setEnabled(True)
        MainWindow.resize(967, 809)
        MainWindow.setMinimumSize(QtCore.QSize(100, 100))
        MainWindow.setMaximumSize(QtCore.QSize(1280, 960))
        font = QtGui.QFont()
        font.setFamily("Arial Black")
        font.setPointSize(14)
        font.setBold(True)
        font.setWeight(75)
        MainWindow.setFont(font)
        MainWindow.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        MainWindow.setTabletTracking(True)
        MainWindow.setLayoutDirection(QtCore.Qt.LeftToRight)
        MainWindow.setAutoFillBackground(False)
        MainWindow.setStyleSheet("")
        MainWindow.setIconSize(QtCore.QSize(30, 30))
        MainWindow.setToolButtonStyle(QtCore.Qt.ToolButtonIconOnly)
        MainWindow.setAnimated(False)
        MainWindow.setTabShape(QtWidgets.QTabWidget.Rounded)
        MainWindow.setDockOptions(QtWidgets.QMainWindow.AllowTabbedDocks)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.label_Blue = QtWidgets.QLabel(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_Blue.sizePolicy().hasHeightForWidth())
        self.label_Blue.setSizePolicy(sizePolicy)
        self.label_Blue.setAutoFillBackground(False)
        self.label_Blue.setStyleSheet("background-color: rgb(0, 0, 255);")
        self.label_Blue.setObjectName("label_Blue")
        self.gridLayout.addWidget(self.label_Blue, 0, 0, 1, 1)
        self.label_Red = QtWidgets.QLabel(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_Red.sizePolicy().hasHeightForWidth())
        self.label_Red.setSizePolicy(sizePolicy)
        self.label_Red.setStyleSheet("background-color: rgb(255, 0, 0);")
        self.label_Red.setObjectName("label_Red")
        self.gridLayout.addWidget(self.label_Red, 0, 2, 1, 1)
        self.label_Green = QtWidgets.QLabel(self.centralwidget)
        self.label_Green.setStyleSheet("background-color: rgb(0, 255, 0);")
        self.label_Green.setObjectName("label_Green")
        self.gridLayout.addWidget(self.label_Green, 0, 1, 1, 1)
        self.horizontalLayout.addLayout(self.gridLayout)
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "XINDA SERVO SYSTEM"))
        self.label_Blue.setText(_translate("MainWindow", "Blue"))
        self.label_Red.setText(_translate("MainWindow", "Red"))
        self.label_Green.setText(_translate("MainWindow", "Green"))

# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'Progress.ui'
##
## Created by: Qt User Interface Compiler version 6.7.1
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
from PySide6.QtWidgets import (QApplication, QLabel, QSizePolicy, QWidget)

class Ui_ProgressBar(object):
    def setupUi(self, ProgressBar):
        if not ProgressBar.objectName():
            ProgressBar.setObjectName(u"ProgressBar")
        ProgressBar.resize(558, 179)
        self.label_Text = QLabel(ProgressBar)
        self.label_Text.setObjectName(u"label_Text")
        self.label_Text.setGeometry(QRect(144, 24, 401, 137))
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_Text.sizePolicy().hasHeightForWidth())
        self.label_Text.setSizePolicy(sizePolicy)
        font = QFont()
        font.setFamilies([u"\u5fae\u8edf\u6b63\u9ed1\u9ad4"])
        font.setPointSize(32)
        font.setBold(True)
        self.label_Text.setFont(font)
        self.label_Text.setLayoutDirection(Qt.LeftToRight)
        self.label_Movie = QLabel(ProgressBar)
        self.label_Movie.setObjectName(u"label_Movie")
        self.label_Movie.setGeometry(QRect(16, 16, 121, 137))
        self.label_Movie.setPixmap(QPixmap(u"Picture/Timer.gif"))
        self.label_Movie.setScaledContents(True)

        self.retranslateUi(ProgressBar)

        QMetaObject.connectSlotsByName(ProgressBar)
    # setupUi

    def retranslateUi(self, ProgressBar):
        ProgressBar.setWindowTitle(QCoreApplication.translate("ProgressBar", u"Warning...", None))
        self.label_Text.setText("")
        self.label_Movie.setText("")
    # retranslateUi


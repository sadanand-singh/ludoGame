#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
ZetCode PyQt5 tutorial

This program creates a skeleton of
a classic GUI application with a menubar,
toolbar, statusbar, and a central widget.

author: Jan Bodnar
website: zetcode.com
last edited: January 2015
"""

import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QLabel
from ludoWindow import Ui_LudoWindow
from PyQt5 import QtCore, QtGui

class LudoWindow(QMainWindow, Ui_LudoWindow):
    def __init__(self, parent=None):
        super(LudoWindow, self).__init__(parent)
        self.setupUi(self)

if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = LudoWindow()
    f = QtGui.QFont( "Arial", 10, QtGui.QFont.Bold)
    stat = QLabel("Sadanand You Got 6")
    stat.setFont(f)
    stat.setAlignment(QtCore.Qt.AlignCenter)
    ex.statusbar.addWidget(stat, 1)

    ex.show()

    sys.exit(app.exec_())

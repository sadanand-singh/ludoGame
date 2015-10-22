#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Ludo PyQt5

This program creates a Ludo Window.
And control a game of it.

author: Sadanand Singh
website: sadanand-singh.github.io
last edited: October 2015
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

    stat = QLabel("Red Starts First")
    stat.setFont(QtGui.QFont("Arial", 10, QtGui.QFont.Bold))
    stat.setAlignment(QtCore.Qt.AlignCenter)
    ex.statusbar.addWidget(stat, 1)

    ex.show()

    sys.exit(app.exec_())

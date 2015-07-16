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
from PyQt5.QtWidgets import QMainWindow, QTextEdit, QAction, QApplication, QPushButton
from PyQt5.QtGui import QIcon
from mainWindow import Ui_LudoWindow

class MainWindow(QMainWindow, Ui_LudoWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MainWindow()

    positions = [(i,j) for i in range(13) for j in range(13)]

    for position in positions:
        button = QPushButton("s")
        ex.gridLayout.addWidget(button,*position)

    ex.show()
    sys.exit(app.exec_())

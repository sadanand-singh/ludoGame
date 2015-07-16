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
from PyQt5.QtWidgets import QMainWindow, QApplication
from ludoWindow import Ui_LudoWindow

class LudoWindow(QMainWindow, Ui_LudoWindow):
    def __init__(self, parent=None):
        super(LudoWindow, self).__init__(parent)
        self.setupUi(self)

if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = LudoWindow()
    ex.show()
    print("Hi")
    sys.exit(app.exec_())

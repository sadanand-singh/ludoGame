# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ludo.ui'
#
# Created by: PyQt5 UI code generator 5.4.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import Qt

class Ui_LudoWindow(object):
    def setupUi(self, LudoWindow):
        LudoWindow.setObjectName("LudoWindow")
        LudoWindow.resize(760, 760)
        LudoWindow.setMinimumSize(QtCore.QSize(760, 760))

        self.centralwidget = QtWidgets.QWidget(LudoWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsView.setObjectName("graphicsView")

        self.scene = QtWidgets.QGraphicsScene(self)
        self.scene.setSceneRect(0, 0, 720, 720)
        self.pen = QtGui.QPen(QtCore.Qt.black)
        self.scene.addLine(0, 0, 0, 720, self.pen)
        self.scene.addLine(720, 0, 720, 720, self.pen)
        self.scene.addLine(0, 0, 720, 0, self.pen)
        self.scene.addLine(0, 720, 720, 720, self.pen)

        self.scene.addRect(0, 0, 288, 288, self.pen, QtGui.QBrush(Qt.green))
        self.scene.addRect(0, 432, 288, 288, self.pen, QtGui.QBrush(Qt.yellow))
        self.scene.addRect(432, 0, 288, 288, self.pen, QtGui.QBrush(Qt.blue))
        self.scene.addRect(432, 432, 288, 288, self.pen, QtGui.QBrush(Qt.red))

        self.scene.addRect(288, 288, 144, 144, self.pen, QtGui.QBrush(Qt.gray))

        self.scene.addLine(288, 288, 432, 432, self.pen)
        self.scene.addLine(432, 288, 288, 432, self.pen)

        self.graphicsView = QtWidgets.QGraphicsView(self.scene)
        self.graphicsView.setObjectName("graphicsView")

        # self.verticalLayout = QtWidgets.QVBoxLayout()
        # self.verticalLayout.setObjectName("verticalLayout")
        # self.verticalLayout.addWidget(self.graphicsView)

        self.verticalLayout.addWidget(self.graphicsView)
        LudoWindow.setCentralWidget(self.centralwidget)

        self.menubar = QtWidgets.QMenuBar(LudoWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 720, 29))
        self.menubar.setObjectName("menubar")
        self.menuNew = QtWidgets.QMenu(self.menubar)
        self.menuNew.setObjectName("menuNew")
        self.menuReset = QtWidgets.QMenu(self.menubar)
        self.menuReset.setObjectName("menuReset")
        self.menuHelp = QtWidgets.QMenu(self.menubar)
        self.menuHelp.setObjectName("menuHelp")
        LudoWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(LudoWindow)
        self.statusbar.setObjectName("statusbar")
        LudoWindow.setStatusBar(self.statusbar)
        self.actionNew_Game = QtWidgets.QAction(LudoWindow)
        self.actionNew_Game.setObjectName("actionNew_Game")
        self.actionLoad_Game = QtWidgets.QAction(LudoWindow)
        self.actionLoad_Game.setObjectName("actionLoad_Game")
        self.actionSave_Game = QtWidgets.QAction(LudoWindow)
        self.actionSave_Game.setObjectName("actionSave_Game")
        self.actionQuit = QtWidgets.QAction(LudoWindow)
        self.actionQuit.setObjectName("actionQuit")
        self.actionHow_to_Play = QtWidgets.QAction(LudoWindow)
        self.actionHow_to_Play.setObjectName("actionHow_to_Play")
        self.actionAbout_Ludo = QtWidgets.QAction(LudoWindow)
        self.actionAbout_Ludo.setObjectName("actionAbout_Ludo")
        self.menuNew.addAction(self.actionNew_Game)
        self.menuNew.addAction(self.actionLoad_Game)
        self.menuNew.addAction(self.actionSave_Game)
        self.menuNew.addSeparator()
        self.menuNew.addAction(self.actionQuit)
        self.menuHelp.addAction(self.actionHow_to_Play)
        self.menuHelp.addAction(self.actionAbout_Ludo)
        self.menubar.addAction(self.menuNew.menuAction())
        self.menubar.addAction(self.menuReset.menuAction())
        self.menubar.addAction(self.menuHelp.menuAction())

        self.retranslateUi(LudoWindow)
        QtCore.QMetaObject.connectSlotsByName(LudoWindow)

    def resizeEvent(self, event):
        self.graphicsView.fitInView(self.scene.itemsBoundingRect())

    def showEvent(self, event):
        self.graphicsView.fitInView(self.scene.itemsBoundingRect())

    def retranslateUi(self, LudoWindow):
        _translate = QtCore.QCoreApplication.translate
        LudoWindow.setWindowTitle(_translate("LudoWindow", "Ludo"))
        self.menuNew.setTitle(_translate("LudoWindow", "New"))
        self.menuReset.setTitle(_translate("LudoWindow", "Reset"))
        self.menuHelp.setTitle(_translate("LudoWindow", "Help"))
        self.actionNew_Game.setText(_translate("LudoWindow", "New Game"))
        self.actionLoad_Game.setText(_translate("LudoWindow", "Load Game"))
        self.actionSave_Game.setText(_translate("LudoWindow", "Save Game"))
        self.actionQuit.setText(_translate("LudoWindow", "Quit"))
        self.actionHow_to_Play.setText(_translate("LudoWindow", "How to Play"))
        self.actionAbout_Ludo.setText(_translate("LudoWindow", "About Ludo"))

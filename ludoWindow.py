# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ludo.ui'
#
# Created by: PyQt5 UI code generator 5.4.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_LudoWindow(object):
    def setupUi(self, LudoWindow):
        LudoWindow.setObjectName("LudoWindow")
        LudoWindow.resize(800, 600)
        LudoWindow.setMinimumSize(QtCore.QSize(800, 600))
        self.centralwidget = QtWidgets.QWidget(LudoWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)

        self.scene = QtWidgets.QGraphicsScene(self)
        self.scene.setSceneRect(0, 0, 500, 500)
        self.pen = QtGui.QPen(QtCore.Qt.green)
        self.scene.addLine(0,0,200,200,self.pen)
        self.scene.addEllipse(400,300,100,100,self.pen)
        # self.graphicsView.fitInView(self.scene.sceneRect(),QtCore.Qt.IgnoreAspectRatio)
        self.graphicsView.setScene(self.scene)

        self.graphicsView.setObjectName("graphicsView")
        self.verticalLayout.addWidget(self.graphicsView)
        LudoWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(LudoWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 800, 29))
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

    def retranslateUi(self, LudoWindow):
        _translate = QtCore.QCoreApplication.translate
        LudoWindow.setWindowTitle(_translate("LudoWindow", "MainWindow"))
        self.menuNew.setTitle(_translate("LudoWindow", "New"))
        self.menuReset.setTitle(_translate("LudoWindow", "Reset"))
        self.menuHelp.setTitle(_translate("LudoWindow", "He&lp"))
        self.actionNew_Game.setText(_translate("LudoWindow", "&New Game"))
        self.actionLoad_Game.setText(_translate("LudoWindow", "&Load Game"))
        self.actionSave_Game.setText(_translate("LudoWindow", "&Save Game"))
        self.actionQuit.setText(_translate("LudoWindow", "&Quit"))
        self.actionHow_to_Play.setText(_translate("LudoWindow", "&How to Play"))
        self.actionAbout_Ludo.setText(_translate("LudoWindow", "&About Ludo"))

#include "game.h"
#include "board.h"
#include "newGameDialog.h"
#include "diceWidget.h"
#include <QtWidgets>

Game::Game(QMainWindow* parent) : QMainWindow(parent),
    board(nullptr),
    dice(nullptr)
{
    QIcon icon(":/images/game");
    this->setWindowIcon(icon);

    createActions();
    createStatusBar();

    board = new Board(this);
    this->setCentralWidget(board);
    this->setFixedSize(635, 720);
}

void Game::createActions()
{
    auto gameMenu = menuBar()->addMenu(tr("&Game"));
    auto gameToolBar = addToolBar(tr("Game"));
    gameToolBar->setMovable(false);
    const QIcon newIcon = QIcon(":/images/icon");
    newGameAction = new QAction(newIcon, tr("&New Game"), this);
    newGameAction->setShortcuts(QKeySequence::New);
    newGameAction->setStatusTip(tr("Start a new game"));
    connect(newGameAction, &QAction::triggered, this, &Game::newGame);
    gameMenu->addAction(newGameAction);
    gameToolBar->addAction(newGameAction);

    const QIcon resetIcon = QIcon(":/images/clear");
    resetAction = new QAction(resetIcon, tr("&Reset"), this);
    connect(resetAction, &QAction::triggered, this, &Game::resetGame);
    resetAction->setShortcuts(QKeySequence::Replace);
    resetAction->setStatusTip(tr("Reset the game"));
    gameMenu->addAction(resetAction);
    resetAction->setEnabled(false);

    gameMenu->addSeparator();

    const QIcon exitIcon = QIcon(":/images/exit");
    auto exitAct = new QAction(exitIcon, tr("&Exit"), this);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    gameMenu->addAction(exitAct);

    menuBar()->addSeparator();

    auto helpMenu = menuBar()->addMenu(tr("&Help"));

    auto howToPlayAct = helpMenu->addAction(tr("&How To Play"), this, &Game::howToPlay);
    howToPlayAct->setStatusTip(tr("Show How to Play Ludo"));

    auto aboutAct = helpMenu->addAction(tr("&About"), this, &Game::about);
    aboutAct->setStatusTip(tr("Show Details About Ludo"));

    auto aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
}

void Game::createStatusBar()
{
    statusLabel = new QLabel(tr("Ready"));
    statusBar()->addPermanentWidget(statusLabel);
}

void Game::newGame()
{
    auto dialog = new NewGameDialog(tr("Choose Players..."));
    connect(dialog, &NewGameDialog::startNewGame, this, &Game::start);
    dialog->exec();
    delete dialog;
}

void Game::start(const QMap<QString, QPair<bool, QString>> playerData)
{
    newGameAction->setEnabled(false);
    resetAction->setEnabled(true);
    statusLabel->setText(tr("Game Started..."));

    for(auto const& key : playerData.keys())
    {
        auto data = playerData.value(key);
        auto isHuman = data.first;
        auto name = data.second;
        // set various parts of the game
    }

    // draw dice at the center of the board
    dice = new DiceWidget();
    dice->setPos(board->getDiceBox()->boundingRect().topLeft());
    board->getScene()->addItem(dice);
    dice->setEnabled(true);

}

void Game::resetGame()
{
    newGameAction->setEnabled(true);
    resetAction->setEnabled(false);
    statusLabel->setText(tr("Game Reset..."));
}

void Game::about()
{
   QMessageBox::about(this, tr("About Ludo"),
            tr("<b>Ludo</b> is a board game. <br>"
               "&copy; Sadanand Singh 2016-17"));
}

void Game::howToPlay()
{
   QMessageBox::about(this, tr("How to Play LUDO"),
            tr("<b>How to Play Ludo</b> <br>"
               "There are 4 colored players, "
               "each having 4 pieces. <br> Red player starts first.<br>"
               "You need to get a SIX to come out of HOME area.<br>"
               "If another colored player falls on your place.<br>"
               "You end up being dead and go back to HOME.<br>"
               "First player to bring all pieces to central <br>"
               "box WINS the game."));
}

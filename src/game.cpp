#include "game.h"
#include "board.h"
#include "player.h"
#include "computerPlayer.h"
#include "homeField.h"
#include "newGameDialog.h"
#include "diceWidget.h"
#include "figure.h"
#include "field.h"
#include "lastField.h"
#include "safeField.h"
#include "startField.h"
#include <QtWidgets>
#include <QTime>

#include <QDebug>

Game::Game(QMainWindow* parent) : QMainWindow(parent),
    newGameAction(nullptr),
    statusLabel(nullptr),
    board(nullptr),
    dice(nullptr),
    playerColors({QColor(205, 92, 92), QColor(85, 107, 47), QColor(218, 165, 32), QColor(0, 191, 255)}),
    playerColorNames({tr("RED"), tr("GREEN"), tr("YELLOW"), tr("BLUE")}),
    currPlayer(nullptr)
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

void Game::start(const QList<QPair<bool, QString>> playerData)
{
    newGameAction->setEnabled(false);
    statusLabel->setText(tr("Game Started..."));

    auto index = 0u;

    for(auto const& data : playerData)
    {
        auto isHuman = data.first;
        auto name = data.second;
        auto color = playerColors.at(index);
        if (not isHuman) name = tr("Computer");

        Player* player;
        if (isHuman)
            player = new Player(name, color, this);
        else
            player = new ComputerPlayer(name, color, this);

        players.append(player);
        connect(player, &Player::continueGame, this, &Game::setCurrentPlayer);
        connect(player, &Player::gameWon, this, &Game::finished);

        auto& figures = player->getFigures();
        auto& startFields = board->getStartField(index);
        player->setStartField(startFields);
        for( auto& startField : startFields)
        {
            auto figure = new Figure(24.0);
            board->getScene()->addItem(figure);
            figure->setPlayer(player);
            figure->setPosition(startField);
            figures.append(figure);

            connect(figure, &Figure::clicked, player, &Player::move);
        }
        ++index;
    }

    // draw dice at the center of the board
    dice = new DiceWidget();
    auto dicePos = board->getDiceBox()->boundingRect().topLeft();
    dicePos -= QPointF(10, 10);
    dice->setPos(dicePos);
    board->getScene()->addItem(dice);

    //Activate Red to start
    currPlayer = players[0];
    showTurn();
    currPlayer->setEnabled(true);
    dice->roll();

    connect(dice, &DiceWidget::diceRolled, this, &Game::updateStatusMessage);
    connect(dice, &DiceWidget::diceRolled, this, &Game::activatePlayerFigures);

    for (auto& player : players)
        connect(dice, &DiceWidget::diceRolled, player, &Player::setDice);
}

void Game::setCurrentPlayer(bool isActive)
{
    if (not isActive)
    {
        currPlayer->setEnabled(false);
        auto indexPlayer = players.indexOf(currPlayer);
        indexPlayer = (indexPlayer != 3) ? indexPlayer + 1 : 0;
        currPlayer = players[indexPlayer];
        currPlayer->setEnabled(true);
    }
    showTurn();
    dice->resetDice();

    delay(1);
    dice->roll();
}

void Game::finished()
{
    auto index = playerColors.indexOf(currPlayer->getColor());
    auto colorName = playerColorNames.at(index);
    auto msg = QStringLiteral("Player: %1 (%2) WON!!").arg(currPlayer->getName()).arg(colorName);
    statusBar()->showMessage(msg);
    statusLabel->setText("");
}

void Game::showTurn()
{
    for(unsigned i = 0u; i < 4; ++i)
    {
        auto rectBox = board->getHome(i);
        rectBox->getHiliteRect()->setVisible(false);
    }

    auto index = playerColors.indexOf(currPlayer->getColor());
    auto colorName = playerColorNames.at(index);
    auto msg = QStringLiteral("Current Player: %1 (%2)").arg(currPlayer->getName()).arg(colorName);
    statusBar()->showMessage(msg);

    //Hilight the current player
    auto rectBox = board->getHome(index);
    rectBox->getHiliteRect()->setVisible(true);
}

void Game::activatePlayerFigures(unsigned diceValue)
{
    auto& figures = currPlayer->getFigures();

    bool isAnyEnabled = false;
    for (auto& figure : figures)
    {
        auto enable = figure->enableIfPossible(diceValue);
        isAnyEnabled = isAnyEnabled or enable;
    }

    // if none enabled, set next player
    if (not isAnyEnabled)
        setCurrentPlayer(false);
}

void Game::updateStatusMessage(unsigned diceValue)
{
    auto index = playerColors.indexOf(currPlayer->getColor());
    auto colorName = playerColorNames.at(index);
    auto msg = QStringLiteral("%1 (%2) You got %3!").arg(currPlayer->getName()).arg(colorName).arg(diceValue);
    statusLabel->setText(msg);
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

void Game::delay(unsigned sec)
{
    QTime dieTime = QTime::currentTime().addSecs(sec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

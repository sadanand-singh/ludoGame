#include "game.h"
#include "board.h"
#include "player.h"
#include "homeField.h"
#include "newGameDialog.h"
#include "diceWidget.h"
#include "figure.h"
#include "field.h"
#include "lastField.h"
#include "safeField.h"
#include <QtWidgets>

#include <QDebug>

Game::Game(QMainWindow* parent) : QMainWindow(parent),
    board(nullptr),
    dice(nullptr),
    playerColors({Qt::red, Qt::green, Qt::yellow, Qt::blue}),
    playerColorNames({tr("RED"), tr("GREEN"), tr("YELLOW"), tr("BLUE")}),
    figureDiameter(24.0),
    figureRadius(12.0),
    currentPlayerId(0)
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

void Game::start(const QList<QPair<bool, QString>> playerData)
{
    newGameAction->setEnabled(false);
    resetAction->setEnabled(true);
    statusLabel->setText(tr("Game Started..."));

    auto index = 0u;

    for(auto const& data : playerData)
    {
        auto colorField = board->getHome(index);
        auto homeField = colorField->getHomeField();

        auto isHuman = data.first;
        auto name = data.second;
        auto color = playerColors.at(index);
        if (not isHuman) name = tr("Computer");

        auto player = new Player(name, color, this);
        player->setHomeField(colorField);
        players.append(player);

        QList<Figure*> figures;
        for( auto& circle : homeField)
        {
            auto center = circle->boundingRect().center();
            auto topLeft = center - QPointF(figureRadius, figureRadius);
            auto figure = new Figure(figureDiameter);
            figure->setPlayer(player);
            figure->setPos(topLeft);
            board->getScene()->addItem(figure);
            figures.append(figure);

            connect(figure, &Figure::clicked, this, &Game::move);
        }
        ++index;
    }

    // draw dice at the center of the board
    dice = new DiceWidget();
    auto dicePos = board->getDiceBox()->boundingRect().topLeft();
    dicePos -= QPointF(10, 10);
    dice->setPos(dicePos);
    board->getScene()->addItem(dice);
    connect(dice, &DiceWidget::diceRolled, this, &Game::updateStatusMessage);

    // Make current player active
    connect(dice, &DiceWidget::diceRolled, this, &Game::activatePlayerFigures);
}

void Game::move(Figure *figure)
{
    if (not figure->isEnabled()) return;

    auto diceValue = dice->value();
    auto position = figure->getPosition();
    auto newPosition = position;
    auto player = figure->getPlayer();
    auto color = player->getColor();

    if (position)
    {
        while (diceValue-- > 0)
        {
            newPosition = newPosition->next(color);
            if (not newPosition) break;
        }

        if (not diceValue)
        {
            if (newPosition)
            {
                board->getScene()->removeItem(figure);

                auto center = newPosition->boundingRect().center();
                auto topLeft = center - QPointF(figureRadius, figureRadius);
                figure->setPos(topLeft);
                board->getScene()->addItem(figure);

                // set all other figures to disabled
                auto figures = player->getFigures();
                for (auto& fig : figures) fig->setEnabled(false);

            }

        }
    }
    else
    {
        if (diceValue)
        {
            board->getScene()->removeItem(figure);

            auto startField = player->getHomeField()->getStartField();
            auto center = startField->boundingRect().center();
            auto topLeft = center - QPointF(figureRadius, figureRadius);
            figure->setPos(topLeft);
            board->getScene()->addItem(figure);

            // set all other figures to disabled
            auto figures = player->getFigures();
            for (auto& fig : figures) fig->setEnabled(false);
        }
    }


}

void Game::activatePlayerFigures(unsigned diceValue)
{
    auto player = players.at(currentPlayerId);
    auto figures = player->getFigures();

    for (auto& figure : figures)
    {
        auto position = figure->getPosition();
        if (position) figure->setEnabled(true);
        else
        {
            if (diceValue) figure->setEnabled(true);
        }
    }
}

void Game::updateStatusMessage(unsigned diceValue)
{
    auto msg = QStringLiteral("%1 (%2) You got %3!").arg(players.at(currentPlayerId)->getName()).arg(playerColorNames.at(currentPlayerId)).arg(diceValue);
    statusLabel->setText(msg);
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

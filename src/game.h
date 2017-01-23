#ifndef GAME_HEADER
#define GAME_HEADER

#include <QMainWindow>

class QAction;
class QLabel;
class Board;
class DiceWidget;
class Player;

class Game : public QMainWindow
{
    Q_OBJECT

    private:
    QString status;
    QAction *newGameAction;
    QAction *resetAction;
    QLabel *statusLabel;
    Board *board;
    DiceWidget *dice;
    QList<QColor> playerColors;
    QList<QString> playerColorNames;
    unsigned currentPlayerId;
    QList<Player*> players;

    protected:
    // void saveState();
    void createActions();
    void createStatusBar();

    private slots:
    void about();
    void howToPlay();
    void newGame();
    void resetGame();
    void updateStatusMessage(int diceValue);
    void start(const QList<QPair<bool, QString>> data);

    public:
    Game(QMainWindow* parent = nullptr);
};

#endif

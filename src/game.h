#ifndef GAME_HEADER
#define GAME_HEADER

#include <QMainWindow>
#include <QMap>
#include <QPair>

class QAction;
class QLabel;

class Game : public QMainWindow
{
    Q_OBJECT

    private:
    QString status;
    QAction *newGameAction;
    QAction *resetAction;
    QLabel *statusLabel;

    protected:
    // void saveState();
    void createActions();
    void createStatusBar();

    private slots:
    void about();
    void howToPlay();
    void newGame();
    void resetGame();
    void start(const QMap<QString, QPair<bool, QString>> data);

    public:
    Game(QMainWindow* parent = nullptr);
};

#endif

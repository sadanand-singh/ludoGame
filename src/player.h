#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <QObject>
#include <QColor>

class HomeField;
class Figure;
class Field;

class Player : public QObject
{
    Q_OBJECT

    protected:
    QList<Figure*> figures;
    HomeField *homeField;
    QColor color;
    bool isActive;
    unsigned figuresRemaining;
    unsigned figuresInHouse;
    unsigned dice;
    unsigned bonusMoves;
    QString name;
    QList<Field*> startField;

    public:
    Player(QString name, QColor color, QObject *parent = nullptr);

    bool hasWon();
    bool hasFigure(Figure *figure);
    bool allFiguresInStartHouse();

    void setFigures(QList<Figure*> figs);
    void setHomeField(HomeField* home);
    void setStartField(QList<Field*>& start);

    QList<Figure*>& getFigures();
    QList<Field*>& getStartField();
    HomeField* getHomeField();
    unsigned getFiguresRemaining();
    QColor getColor();
    QString getName();

    public slots:
    void move(Figure *figure);
    void setDice(unsigned dice);

    signals:
    void updateCurrent(Player *player);
};
#endif

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
    QColor color;
    bool isActive;
    unsigned dice;
    int bonusMoves;
    QString name;
    QList<Field*> startField;

    public:
    Player(QString name, QColor color, QObject *parent = nullptr);

    bool hasWon();
    bool hasFigure(Figure *figure);

    void setFigures(QList<Figure*> figs);
    void setStartField(QList<Field*>& start);
    void setEnabled(bool enable);

    QList<Figure*>& getFigures();
    QList<Field*>& getStartField();
    QColor getColor();
    QString getName();

    public slots:
    void move(Figure *figure);
    void setDice(unsigned dice);

    signals:
    void continueGame(bool isActive);
    void gameWon();
};
#endif

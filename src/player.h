#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include <QObject>
#include <QColor>

class HomeField;
class Figure;

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
    QString name;

    public:
    Player(QString name, QColor color, QObject *parent = nullptr);

    bool hasWon();
    bool hasFigure(Figure *figure);
    bool allFiguresInStartHouse();

    void setFigures(QList<Figure*> figs);
    void setHomeField(HomeField* home);

    QList<Figure*>& getFigures();
    HomeField* getHomeField();
    unsigned getFiguresRemaining();
    QColor getColor();
    QString getName();
};
#endif

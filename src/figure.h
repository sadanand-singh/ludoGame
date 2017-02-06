#ifndef FIGURE_HEADER
#define FIGURE_HEADER

#include <QGraphicsEllipseItem>
#include <QObject>

class Player;
class Field;

class Figure : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    protected:
    Player *player;
    Field *currPos;
    qreal diameter;
    bool enabled;
    QColor color;

    public:
    Figure(qreal r, QGraphicsItem* parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *e) Q_DECL_OVERRIDE;
    void setEnabled(bool enabled);

    void setPlayer(Player *player);
    void setPosition(Field *pos);
    void setDiameter(qreal diameter);
    bool eventFilter(QObject *obj, QEvent *event);
    QColor getColor();

    Player* getPlayer();
    Field* getPosition();
    bool isEnabled();
    qreal getDiameter();

    signals:
    void clicked(Figure*);
    void enter(Figure*);
    void leave(Figure*);
    void moved(Figure*);
};

#endif

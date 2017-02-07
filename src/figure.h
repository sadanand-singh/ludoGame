#ifndef FIGURE_HEADER
#define FIGURE_HEADER

#include <QGraphicsEllipseItem>
#include <QObject>

class Player;
class Field;
class QGraphicsRectItem;

class Figure : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

    protected:
    Player *player;
    Field *currPos;
    Field *resultPos;
    qreal diameter;
    bool enabled;
    QColor color;
    QGraphicsRectItem *hilight;

    void findResultPosition(int dice);

    public:
    Figure(qreal r, QGraphicsItem* parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *e) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
    void setEnabled(bool enabled);
    bool enableIfPossible(unsigned dice);
    void moveToHome();

    void setPlayer(Player *player);
    void setPosition(Field *pos);
    void setDiameter(qreal diameter);
    QColor getColor();

    Player* getPlayer();
    Field* getPosition();
    Field* getResultPosition();
    QGraphicsRectItem* getHilight();

    bool isEnabled();
    qreal getDiameter();

    private slots:
    void hilightField(Figure *fig);
    void unhilightField(Figure *fig);

    signals:
    void clicked(Figure*);
    void enter(Figure*);
    void leave(Figure*);
    void moved(Figure*);
};

#endif

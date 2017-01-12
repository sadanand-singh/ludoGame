#ifndef HOMEFIELD_HEADER
#define HOMEFIELD_HEADER

#include <QtCore>
class QGraphicsEllipseItem;
class QGraphicsRectItem;
class QGraphicsScene;
class QColor;

class HomeField
{
    private:
    qreal startX;
    qreal startY;
    const QColor& color;
    QGraphicsRectItem *rect;
    QList<QGraphicsEllipseItem*> circles;

    public:
    HomeField(qreal x, qreal y, QColor color, QGraphicsScene *scene);
    QList<QGraphicsEllipseItem*> getHomeField();
    QColor getColor();

};

#endif

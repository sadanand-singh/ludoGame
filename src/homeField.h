#ifndef HOMEFIELD_HEADER
#define HOMEFIELD_HEADER

#include <QtCore>
class QGraphicsEllipseItem;
class QGraphicsRectItem;
class QGraphicsPolygonItem;
class QGraphicsScene;
class QColor;

class HomeField
{
    private:
    qreal startX;
    qreal startY;
    const QColor& color;
    QGraphicsRectItem *rect;
    QGraphicsPolygonItem *triangle;
    QList<QGraphicsEllipseItem*> circles;

    public:
    HomeField(qreal x, qreal y, qreal r, QColor color, QGraphicsScene *scene);
    QList<QGraphicsEllipseItem*> getHomeField();
    QColor getColor();
    QGraphicsPolygonItem* getEndZone();

};

#endif

#ifndef HOMEFIELD_HEADER
#define HOMEFIELD_HEADER

#include <QtCore>
#include <QObject>
class QGraphicsEllipseItem;
class QGraphicsRectItem;
class QGraphicsPolygonItem;
class QGraphicsScene;
class QColor;

class HomeField : public QObject
{
    private:
    qreal startX;
    qreal startY;
    const QColor& color;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *hiliteRect;
    QGraphicsPolygonItem *triangle;
    QList<QGraphicsEllipseItem*> circles;

    public:
    HomeField(qreal x, qreal y, qreal r, QColor color, QGraphicsScene *scene, QObject *parent);
    QList<QGraphicsEllipseItem*> getHomeField();
    QGraphicsPolygonItem* getEndZone();
    QGraphicsRectItem* getHiliteRect();
};

#endif

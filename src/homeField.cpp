#include "homeField.h"
#include "field.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QPolygonF>

HomeField::HomeField(qreal x, qreal y, qreal r, QColor c, QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    startX(x),
    startY(y),
    color(c),
    rect(nullptr),
    triangle(nullptr),
    nextField(nullptr)
{
    rect = scene->addRect(QRectF(x, y, 240, 240));
    rect->setPen(QPen(Qt::black, 2.0));
    rect->setBrush(QBrush(color));

    QGraphicsEllipseItem *c1 = scene->addEllipse(startX + 40, startY + 40, 60, 60);
    c1->setPen(QPen(Qt::black, 2.0));
    c1->setBrush(QBrush(Qt::white));
    circles.append(c1);

    QGraphicsEllipseItem *c2 = scene->addEllipse(startX + 140, startY + 40, 60, 60);
    c2->setPen(QPen(Qt::black, 2.0));
    c2->setBrush(QBrush(Qt::white));
    circles.append(c2);

    QGraphicsEllipseItem *c3 = scene->addEllipse(startX + 40, startY + 140, 60, 60);
    c3->setPen(QPen(Qt::black, 2.0));
    c3->setBrush(QBrush(Qt::white));
    circles.append(c3);

    QGraphicsEllipseItem *c4 = scene->addEllipse(startX + 140, startY + 140, 60, 60);
    c4->setPen(QPen(Qt::black, 2.0));
    c4->setBrush(QBrush(Qt::white));
    circles.append(c4);

    // Describe a closed triangle
    QPolygonF T;
    T.append(QPointF(240, 240));
    T.append(QPointF(240, 360));
    T.append(QPointF(300, 300));
    T.append(QPointF(240, 240));
    // Add the triangle polygon to the scene
    triangle = scene->addPolygon(T);
    triangle->setPen(QPen(Qt::black, 2.0));
    triangle->setBrush(QBrush(color));
    triangle->setTransformOriginPoint(QPointF(300, 300));
    triangle->setRotation(r);
}

QList<QGraphicsEllipseItem*> HomeField::getHomeField()
{
    return this->circles;
}

QColor HomeField::getColor()
{
    return this->color;
}

QGraphicsPolygonItem* HomeField::getEndZone()
{
    return this->triangle;
}

void HomeField::setNextField(Field *field)
{
    this->nextField = field;
}

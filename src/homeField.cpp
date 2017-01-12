#include "homeField.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

HomeField::HomeField(qreal x, qreal y, QColor c, QGraphicsScene *scene) :
    startX(x),
    startY(y),
    color(c),
    rect(nullptr)
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
}

QList<QGraphicsEllipseItem*> HomeField::getHomeField()
{
    return this->circles;
}

QColor HomeField::getColor()
{
    return this->color;
}

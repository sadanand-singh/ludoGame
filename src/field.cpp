#include "field.h"
#include <QPen>

Field::Field(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    QGraphicsRectItem(x, y, w, h, parent),
    nextField(nullptr),
    safeField(nullptr),
    isSafe(false),
    safeColor(QColor()),
    isSpecial(false)
{
    setPen(QPen(Qt::black, 2.0));
}

void Field::setSafeField(Field *field)
{
    safeField = field;
}

void Field::setNextField(Field *field)
{
    nextField = field;
}

void Field::makeSafe(QColor color)
{
    isSafe = true;
    safeColor = color;

}

void Field::makeSpecial()
{
    isSpecial = true;
}

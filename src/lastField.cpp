#include "lastField.h"

LastField::LastField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    Field(x, y, w, h, parent),
    color(QColor()),
    nextSafe(nullptr)
{}

void LastField::setColor(QColor color)
{
    this->color = color;
}

void LastField::setSafeField(Field *field)
{
    this->nextSafe = field;
}

Field* LastField::next(QColor color)
{
    if (color == this->color) return nextSafe;

    return nextField;
}

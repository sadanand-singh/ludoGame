#include "safeField.h"
#include "figure.h"
#include <QBrush>

SafeField::SafeField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    Field(x, y, w, h, parent),
    color(QColor())
{}

void SafeField::setColor(QColor color)
{
    this->color = color;
    setBrush(QBrush(color));
}

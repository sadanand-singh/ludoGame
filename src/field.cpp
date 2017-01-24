#include "field.h"
#include <QPen>

Field::Field(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    QGraphicsRectItem(x, y, w, h, parent),
    nextField(nullptr),
    isSpecial(false)
{
    setPen(QPen(Qt::black, 2.0));
}

void Field::setNextField(Field *field)
{
    nextField = field;
}

void Field::makeSpecial()
{
    isSpecial = true;
}

Field* Field::next(QColor color)
{
    Q_UNUSED (color);
    return nextField;
}

void Field::addFigure(Figure *fig)
{
    figures.append(fig);
}

void Field::removeFigure(Figure *fig)
{
    figures.removeAll(fig);
}

void Field::setColor(QColor color)
{
    Q_UNUSED (color);
}

void Field::setSafeField(Field *field)
{
    Q_UNUSED (field);
}

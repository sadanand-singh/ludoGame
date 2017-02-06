#include "endField.h"

EndField::EndField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    Field(x, y, w, h, parent)
{
    this->setVisible(false);
}


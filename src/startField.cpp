#include "startField.h"

StartField::StartField(QRectF r, QGraphicsItem* parent) :
    Field(r.x() + 1.0, r.y() + 1.0, r.width() - 2.0, r.height() - 2.0, parent)
{
    this->setVisible(false);
}

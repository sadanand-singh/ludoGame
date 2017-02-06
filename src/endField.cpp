#include "endField.h"
#include "figure.h"

EndField::EndField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    Field(x, y, w, h, parent)
{
    this->setVisible(false);
}

void EndField::drawFigures()
{
    for (auto& fig : figures)
        fig->setDiameter(0.5 * fig->getDiameter());

    Field::drawFigures();
}

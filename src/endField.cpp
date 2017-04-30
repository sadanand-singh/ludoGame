#include "endField.h"
#include "figure.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>

EndField::EndField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    Field(x, y, w, h, parent)
{
    this->setVisible(false);
    this->special = true;
}

void EndField::drawFigures()
{
    auto scene = this->scene();

    unsigned figureCount = 0u;
    if (this->text)
    {
        scene->removeItem(this->text);
        delete this->text;
        this->text = nullptr;
    }

    for (auto& fig : figures)
    {
        ++figureCount;
        scene->removeItem(fig);
        auto center = this->boundingRect().center();
        fig->setDiameter(18.0);
        auto figureRadius = 0.5 * fig->getDiameter();
        auto topLeft = center - QPointF(figureRadius, figureRadius);
        fig->setPos(topLeft);
        scene->addItem(fig);
    }
    if (figureCount > 1)
    {
        this->text = new QGraphicsTextItem;
        auto fig = figures.at(0);
        auto figureRadius = 0.5 * fig->getDiameter();
        auto center = this->boundingRect().center();
        auto topLeft = center - QPointF(figureRadius, figureRadius);
        topLeft += QPointF(2, -2);
        this->text->setPos(topLeft);
        this->text->setFont(QFont("Times", 8, QFont::Bold));
        this->text->setPlainText(QString::number(figureCount));
        scene->addItem(this->text);
    }
}

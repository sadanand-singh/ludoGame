#include "specialField.h"
#include "figure.h"
#include <QBrush>
#include <QGraphicsScene>

SpecialField::SpecialField(QRectF r, QGraphicsItem* parent) :
    Field(r.x() + 1.0, r.y() + 1.0, r.width() - 2.0, r.height() - 2.0, parent),
    colorCounts({0, 0, 0, 0}),
    figureColors(0),
    texts({nullptr, nullptr, nullptr, nullptr}),
    colors({Qt::red, Qt::green, Qt::yellow, Qt::blue})
{
    special = true;
}

void SpecialField::addFigure(Figure *fig)
{
    auto color = fig->getColor();
    if (++colorCounts[colors.indexOf(color)] == 1) ++figureColors;

    Field::addFigure(fig);
}

void SpecialField::removeFigure(Figure *fig)
{
    auto color = fig->getColor();
    if (--colorCounts[colors.indexOf(color)] == 0) --figureColors;

    Field::removeFigure(fig);
}

void SpecialField::drawFigures()
{
    auto scene = this->scene();

    for (auto& textLocal : texts)
    {
        if (textLocal)
        {
            scene->removeItem(textLocal);
            delete textLocal;
            textLocal = nullptr;
        }
    }

    if (figureColors == 1)
    {
        auto color = figures.at(0)->getColor();
        this->text = texts[colors.indexOf(color)];
        Field::drawFigures();
        return;
    }


    for (auto& fig : figures)
    {
        auto color = fig->getColor();
        scene->removeItem(fig);

        auto center = this->boundingRect().center();
        getNewCenter(center, colors.indexOf(color));
        auto figureRadius = 0.125 * fig->getDiameter();
        auto topLeft = center - QPointF(figureRadius, figureRadius);

        fig->setPos(topLeft);
        scene->addItem(fig);
    }

    for (auto& count : colorCounts)
    {
        if (count > 1)
        {
            text = new QGraphicsTextItem;
            auto index = colorCounts.indexOf(count);
            auto center = this->boundingRect().center();
            getNewCenter(center, index);
            auto figureRadius = 0.125 * figures.at(0)->getDiameter();
            auto topLeft = center - QPointF(figureRadius, figureRadius);
            topLeft += QPointF(5, 0);
            text->setPos(topLeft);
            text->setFont(QFont("Times", 10, QFont::Bold));
            text->setPlainText(QString::number(count));
            scene->addItem(text);
            texts[index] = text;
        }
    }
}

void SpecialField::getNewCenter(QPointF& center, unsigned index)
{
    QPointF shift;
    switch(index)
    {
        case 0 : shift = QPointF(-10.0, -10.0);
                 break;
        case 1 : shift = QPointF(10.0, -10.0);
                 break;
        case 2 : shift = QPointF(10.0, 10.0);
                 break;
        case 3 : shift = QPointF(-10.0, 10.0);
                 break;
    }

    center += shift;
}

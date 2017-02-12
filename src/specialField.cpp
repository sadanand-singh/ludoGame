#include "specialField.h"
#include "figure.h"
#include <QBrush>
#include <QGraphicsScene>

SpecialField::SpecialField(QRectF r, QGraphicsItem* parent) :
    Field(r.x() + 1.0, r.y() + 1.0, r.width() - 2.0, r.height() - 2.0, parent),
    colorCounts({0, 0, 0, 0}),
    figureColors(0),
    texts({nullptr, nullptr, nullptr, nullptr}),
    colors({QColor(205, 92, 92), QColor(85, 107, 47), QColor(218, 165, 32), QColor(0, 191, 255)})
{
    special = true;
    setBrush(QBrush(Qt::lightGray));
}

void SpecialField::addFigure(Figure *fig)
{
    auto color = fig->getColor();
    if (colorCounts[colors.indexOf(color)] == 0) ++figureColors;

    colorCounts[colors.indexOf(color)] += 1;

    Field::addFigure(fig);
}

void SpecialField::removeFigure(Figure *fig)
{
    auto color = fig->getColor();
    if (colorCounts[colors.indexOf(color)] == 1) --figureColors;
    colorCounts[colors.indexOf(color)] -= 1;

    Field::removeFigure(fig);
}

void SpecialField::drawFigures()
{
    auto scene = this->scene();
    if(this->text)
    {
        scene->removeItem(this->text);
        delete this->text;
        this->text = nullptr;
    }

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
        fig->setDiameter(16.0);
        auto figureRadius = 0.5 * fig->getDiameter();
        auto topLeft = center - QPointF(figureRadius, figureRadius);

        fig->setPos(topLeft);
        scene->addItem(fig);
    }

    for (auto& count : colorCounts)
    {
        if (count > 1)
        {
            auto textLocal = new QGraphicsTextItem;
            auto index = colorCounts.indexOf(count);
            auto center = this->boundingRect().center();
            getNewCenter(center, index);
            auto topLeft = center - QPointF(8.0, 8.0);
            topLeft += QPointF(5, 0);
            textLocal->setPos(topLeft);
            textLocal->setFont(QFont("Times", 10, QFont::Bold));
            textLocal->setPlainText(QString::number(count));
            scene->addItem(textLocal);
            texts[index] = textLocal;
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
        default: break;
    }

    center += shift;
}

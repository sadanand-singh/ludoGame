#include "field.h"
#include "figure.h"
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

Field::Field(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) :
    QGraphicsRectItem(x, y, w, h, parent),
    nextField(nullptr),
    prevField(nullptr),
    special(false),
    text(nullptr)
{
    setPen(QPen(Qt::black, 2.0));
}

void Field::setNextField(Field *field)
{
    nextField = field;
}

void Field::setPreviousField(Field *field)
{
    prevField = field;
}

Field* Field::next(QColor color)
{
    Q_UNUSED (color);
    return nextField;
}

Field* Field::previous()
{
    return prevField;
}

QList<Figure*>& Field::getFigures()
{
    return figures;
}

void Field::addFigure(Figure *fig)
{
    figures.append(fig);
    drawFigures();
}

void Field::removeFigure(Figure *fig)
{
    figures.removeAll(fig);
    drawFigures();
}

void Field::setColor(QColor color)
{
    Q_UNUSED (color);
}

void Field::setSafeField(Field *field)
{
    Q_UNUSED (field);
}

void Field::drawFigures()
{
    auto scene = this->scene();

    unsigned figureCount = 0u;
    if (text)
    {
        scene->removeItem(text);
        delete text;
        text = nullptr;
    }

    for (auto& fig : figures)
    {
        ++figureCount;
        scene->removeItem(fig);
        auto center = this->boundingRect().center();
        fig->setDiameter(24.0);
        auto figureRadius = 0.5 * fig->getDiameter();
        auto topLeft = center - QPointF(figureRadius, figureRadius);
        fig->setPos(topLeft);
        scene->addItem(fig);
    }
    if (figureCount > 1)
    {
        text = new QGraphicsTextItem;
        auto fig = figures.at(0);
        auto figureRadius = 0.5 * fig->getDiameter();
        auto center = this->boundingRect().center();
        auto topLeft = center - QPointF(figureRadius, figureRadius);
        topLeft += QPointF(5, 0);
        text->setPos(topLeft);
        text->setFont(QFont("Times", 10, QFont::Bold));
        text->setPlainText(QString::number(figureCount));
        scene->addItem(text);
    }
}

bool Field::isSpecial()
{
    return special;
}
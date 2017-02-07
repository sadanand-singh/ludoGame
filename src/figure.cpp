#include "figure.h"
#include "player.h"
#include "field.h"
#include "endField.h"
#include "startField.h"
#include <QPen>
#include <QEvent>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

Figure::Figure(qreal r, QGraphicsItem* parent) :
    QGraphicsEllipseItem(0.0, 0.0, r, r, parent),
    player(nullptr),
    currPos(nullptr),
    resultPos(nullptr),
    diameter(r),
    enabled(false),
    hilight(nullptr)
{
    setAcceptHoverEvents(true);
    setPen(QPen(Qt::black, 2.0));
    connect(this, &Figure::enter, this, &Figure::hilightField);
    connect(this, &Figure::leave, this, &Figure::unhilightField);
}

void Figure::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    if (not enabled) return;
    emit enter(this);
}

void Figure::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    if (not enabled) return;
    emit leave(this);
}

void Figure::hilightField(Figure *fig)
{
    auto color = fig->getColor();
    auto pos = fig->getResultPosition();
    auto scene = pos->scene();
    hilight = scene->addRect(pos->boundingRect());
    hilight->setPen(QPen(color, 4.0));
}

void Figure::unhilightField(Figure *fig)
{
    if (hilight)
    {
        auto pos = fig->getResultPosition();
        auto scene = pos->scene();
        scene->removeItem(hilight);
        delete hilight;
        hilight = nullptr;
    }
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (not enabled) return;
    emit clicked(this);
}

void Figure::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

bool Figure::isEnabled()
{
    return enabled;
}

void Figure::setPlayer(Player *player)
{
    this->player = player;
    color = player->getColor();
    this->setBrush(QBrush(color));
}

QColor Figure::getColor()
{
    return color;
}

void Figure::setPosition(Field *pos)
{
    unhilightField(this);

    // Remove this figure from currPos
    if (this->currPos) this->currPos->removeFigure(this);

    // set new Position
    this->currPos = pos;
    this->currPos->addFigure(this);
}

Player* Figure::getPlayer()
{
    return player;
}

Field* Figure::getPosition()
{
    return currPos;
}

Field* Figure::getResultPosition()
{
    return resultPos;
}

qreal Figure::getDiameter()
{
    return diameter;
}

void Figure::setDiameter(qreal diameter)
{
    this->diameter = diameter;
}

bool Figure::enableIfPossible(unsigned dice)
{
    auto enabled = false;
    if (dynamic_cast<EndField*> (currPos))
        return enabled;

    if (dynamic_cast<StartField*> (currPos))
    {
        if(dice == 6)
        {
            this->setEnabled(true);
            enabled = true;
            resultPos = currPos->next(color);
        }
        return enabled;
    }

    findResultPosition(dice);
    if (resultPos)
    {
        this->setEnabled(true);
        enabled = true;
    }
    return enabled;
}

void Figure::findResultPosition(int dice)
{
    resultPos = currPos;
    qDebug() << "dice = " << dice;

    while (dice > 0)
    {
        --dice;
        resultPos = resultPos->next(color);
        if (not resultPos)
            break;
    }
}

QGraphicsRectItem* Figure::getHilight()
{
    return hilight;
}

void Figure::moveToHome()
{
    auto player = getPlayer();
    auto& startField = player->getStartField();
    auto index = player->getFigures().indexOf(this);
    auto start = startField.at(index);
    setPosition(start);
}

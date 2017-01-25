#include "figure.h"
#include "player.h"
#include "field.h"
#include <QPen>
#include <QEvent>

Figure::Figure(qreal r, QGraphicsItem* parent) :
    QGraphicsEllipseItem(0.0, 0.0, r, r, parent),
    player(nullptr),
    currPos(nullptr),
    enabled(false)
{
    setPen(QPen(Qt::black, 2.0));
}

bool Figure::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this)
    {
        if(event->type() == QEvent::Enter)
        {
            emit enter(this);
            return true;
        }

        if(event->type() == QEvent::Leave)
        {
            emit leave(this);
            return true;
        }
    }
return false;
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (not enabled) return;

    emit clicked(this);
    QGraphicsEllipseItem::mousePressEvent(e);
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
    auto color = player->getColor();
    this->setBrush(QBrush(color));
}

void Figure::setPosition(Field *pos)
{
    this->currPos = pos;
}

Player* Figure::getPlayer()
{
    return player;
}

Field* Figure::getPosition()
{
    return currPos;
}
#include "diceWidget.h"
#include <QPainter>
#include <QPixmap>
#include <QGraphicsRotation>
#include <QPropertyAnimation>

DiceWidget::DiceWidget(QGraphicsItem *parent) : QGraphicsPixmapItem(parent),
    enabled(true),
    dice(0u),
    uniform_dist(std::uniform_int_distribution<int>(1, 6))
{
    images.append(QPixmap(":/images/dice"));
    images.append(QPixmap(":/images/dice1"));
    images.append(QPixmap(":/images/dice2"));
    images.append(QPixmap(":/images/dice3"));
    images.append(QPixmap(":/images/dice4"));
    images.append(QPixmap(":/images/dice5"));
    images.append(QPixmap(":/images/dice6"));
    setPixmap(images.at(0));
}

void DiceWidget::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (not enabled) return;
    QGraphicsPixmapItem::mousePressEvent(e);
}

void DiceWidget::throwDice()
{
    std::mt19937 e1(r());
    dice = uniform_dist(e1);
    setPixmap(images.at(dice));
    enabled = false;
    emit diceRolled(dice);
}

void DiceWidget::resetDice()
{
    setPixmap(images[0]);
    enabled = true;
}

void DiceWidget::roll()
{
    if (not enabled) return;

    setPixmap(images.at(0));

    auto graphicsRotation = new QGraphicsRotation();
    graphicsRotation->setAxis(Qt::YAxis);
    graphicsRotation->setAngle(0);
    graphicsRotation->setOrigin(QVector3D(QPointF(35, 35)));
    QList<QGraphicsTransform*> t {graphicsRotation};
    setTransformations(t);

    auto animation = new QPropertyAnimation(graphicsRotation, "angle");
    animation->setDuration(500);
    animation->setStartValue(graphicsRotation->angle());
    animation->setEndValue(360);
    animation->start();

    connect(animation, &QAbstractAnimation::finished, this, &DiceWidget::throwDice);
}

void DiceWidget::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

unsigned DiceWidget::value()
{
    return dice;
}

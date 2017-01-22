#include "diceWidget.h"
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QStyleOptionViewItemV4>
#include <QTimer>
#include <QPropertyAnimation>

DiceWidget::DiceWidget(QGraphicsItem *parent) : QGraphicsObject(parent),
    enabled(true),
    dice(0),
    uniform_dist(std::uniform_int_distribution<int>(1, 6))
{
    images.append(new QPixmap(":/images/dice"));
    images.append(new QPixmap(":/images/dice1"));
    images.append(new QPixmap(":/images/dice2"));
    images.append(new QPixmap(":/images/dice3"));
    images.append(new QPixmap(":/images/dice4"));
    images.append(new QPixmap(":/images/dice5"));
    images.append(new QPixmap(":/images/dice6"));
    this->setTransformOriginPoint(35, 35);
}

QRectF DiceWidget::boundingRect() const
{
    return QRectF(0, 0, 70, 70);
}

void DiceWidget::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (not enabled) return;

    roll();
    QGraphicsItem::mousePressEvent(e);
}

void DiceWidget::throwDice()
{
    std::mt19937 e1(r());
    dice = uniform_dist(e1);
    update();
    enabled = false;
    emit diceRolled(dice);
}

void DiceWidget::resetDice()
{
    dice = 0;
    update();
    enabled = true;
}

void DiceWidget::roll()
{
    if (not enabled) return;

    dice = 0;
    auto animation = new QPropertyAnimation(this, "rotation");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(360);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    connect(animation, &QAbstractAnimation::finished, this, &DiceWidget::throwDice);
}

void DiceWidget::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

void DiceWidget::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPixmap pixmap(*images[dice]);

    p->drawPixmap(-5, -5, pixmap);
}


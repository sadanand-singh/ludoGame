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

    QTimer::singleShot(1000, this, SLOT(roll()));
    QGraphicsItem::mousePressEvent(e);
}

void DiceWidget::roll()
{
    if (not enabled) return;

    std::mt19937 e1(r());
    dice = uniform_dist(e1);
    auto animation = new QPropertyAnimation(this, "rotation");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(360);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    update();
    enabled = false;
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


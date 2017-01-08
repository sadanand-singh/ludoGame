#include "playerIcon.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

PlayerIcon::PlayerIcon(QColor color, QWidget* parent) : QWidget(parent),
    playerColor(color)
{
    this->setFixedSize(20, 20);
}

void PlayerIcon::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(playerColor));
    painter.setPen(QPen(Qt::black , 0.5));
    painter.drawEllipse(this->rect().adjusted(1, 1, -1, -1));
}

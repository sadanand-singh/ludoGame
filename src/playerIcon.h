#ifndef PLAYERICON_HEADER
#define PLAYERICON_HEADER

#include <QWidget>

class QColor;

class PlayerIcon : public QWidget
{
    QColor playerColor;
    public:
    PlayerIcon(QColor color, QWidget* parent = nullptr);
    void paintEvent(QPaintEvent* event);
};

#endif

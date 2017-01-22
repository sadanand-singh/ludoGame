#ifndef FIELD_HEADER
#define FIELD_HEADER

#include <QGraphicsRectItem>
#include <QObject>

class Field : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    protected:
    Field *nextField;
    Field *safeField;
    bool isSafe;
    QColor safeColor;
    bool isSpecial;

    public:
    Field(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);

    void setSafeField(Field *field);
    void setNextField(Field *field);
    void makeSafe(QColor color);
    void makeSpecial();
};

#endif
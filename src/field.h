#ifndef FIELD_HEADER
#define FIELD_HEADER

#include <QGraphicsRectItem>
#include <QObject>

class Figure;

class Field : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    protected:
    Field *nextField;
    bool isSpecial;
    QList<Figure*> figures;

    public:
    Field(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);

    void setNextField(Field *field);
    void makeSpecial();
    void addFigure(Figure *fig);
    void removeFigure(Figure *fig);
    virtual Field* next(QColor color);
    virtual void setColor(QColor color);
    virtual void setSafeField(Field *field);
};

#endif
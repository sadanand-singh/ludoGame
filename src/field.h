#ifndef FIELD_HEADER
#define FIELD_HEADER

#include <QGraphicsRectItem>
#include <QObject>

class Figure;
class QGraphicsTextItem;

class Field : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    protected:
    Field *nextField;
    Field *prevField;
    bool special;
    QList<Figure*> figures;
    QGraphicsTextItem *text;

    public:
    Field(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);
    void setNextField(Field *field);
    void setPreviousField(Field *field);
    QList<Figure*>& getFigures();
    bool isSpecial();
    virtual void addFigure(Figure *fig);
    virtual void removeFigure(Figure *fig);
    virtual Field* next(QColor color);
    virtual Field* previous();
    virtual void setColor(QColor color);
    virtual void setSafeField(Field *field);
    virtual void drawFigures();
};

#endif

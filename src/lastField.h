#ifndef LASTFIELD_HEADER
#define LASTFIELD_HEADER

#include "field.h"

class LastField : public Field
{
    Q_OBJECT

    protected:
    QColor color;
    Field* nextSafe;

    public:
    LastField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);

    virtual void setSafeField(Field *field) Q_DECL_OVERRIDE;
    virtual void setColor(QColor color) Q_DECL_OVERRIDE;
    virtual Field* next(QColor color) Q_DECL_OVERRIDE;

    QColor getColor();
};

#endif

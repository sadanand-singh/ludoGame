#ifndef SAFEFIELD_HEADER
#define SAFEFIELD_HEADER

#include "field.h"

class SafeField : public Field
{
    Q_OBJECT

    protected:
    QColor color;

    public:
    SafeField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);

    virtual void setColor(QColor color) Q_DECL_OVERRIDE;
};

#endif
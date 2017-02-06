#ifndef ENDFIELD_HEADER
#define ENDFIELD_HEADER

#include "field.h"

class EndField : public Field
{
    Q_OBJECT

    public:
    EndField(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = nullptr);
    virtual void drawFigures() Q_DECL_OVERRIDE;
};

#endif

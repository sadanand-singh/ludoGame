#ifndef STARTFIELD_HEADER
#define STARTFIELD_HEADER

#include "field.h"

class StartField : public Field
{
    Q_OBJECT

    public:
    StartField(QRectF rect, QGraphicsItem* parent = nullptr);
};

#endif

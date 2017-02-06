#ifndef SSPECIALFIELD_HEADER
#define SSPECIALFIELD_HEADER

#include "field.h"
#include <QColor>

class SpecialField : public Field
{
    Q_OBJECT
    QList<unsigned> colorCounts;
    unsigned figureColors;
    QList<QGraphicsTextItem*> texts;

    QList<QColor> colors;
    void getNewCenter(QPointF& center, unsigned index);

    public:
    SpecialField(QRectF rect, QGraphicsItem* parent = nullptr);

    virtual void addFigure(Figure *fig) Q_DECL_OVERRIDE;
    virtual void removeFigure(Figure *fig) Q_DECL_OVERRIDE;
    virtual void drawFigures() Q_DECL_OVERRIDE;
};

#endif

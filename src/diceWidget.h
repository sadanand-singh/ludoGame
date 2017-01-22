#ifndef DICEWIDGET_HEADER
#define DICEWIDGET_HEADER

#include <QGraphicsObject>
#include <QList>
#include <random>

class QPixmap;

class DiceWidget : public QGraphicsObject
{
    Q_OBJECT

    protected:
    bool enabled;
    int dice;
    QList<QPixmap*> images;
    std::random_device r;
    std::uniform_int_distribution<int> uniform_dist;

    public:
    explicit DiceWidget(QGraphicsItem *parent = 0);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void setEnabled(bool enabled);
    // overriding paint()
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *e) Q_DECL_OVERRIDE;
    void resetDice();

    signals:
    void diceRolled(const int dice);

    private slots:
    void roll();
    void throwDice();
};

#endif

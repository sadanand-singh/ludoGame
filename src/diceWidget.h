#ifndef DICEWIDGET_HEADER
#define DICEWIDGET_HEADER

#include <QObject>
#include <QGraphicsPixmapItem>
#include <random>

class DiceWidget : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    protected:
    bool enabled;
    unsigned dice;
    QList<QPixmap> images;
    std::random_device r;
    std::uniform_int_distribution<int> uniform_dist;

    public:
    explicit DiceWidget(QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *e) Q_DECL_OVERRIDE;
    void setEnabled(bool enabled);
    void resetDice();
    unsigned value();

    signals:
    void diceRolled(const unsigned dice);

    private slots:
    void roll();
    void throwDice();
};

#endif

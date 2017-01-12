#ifndef BOARD_HEADER
#define BOARD_HEADER

#include <QWidget>
#include <QList>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsRectItem;
class QGraphicsItemGroup;
class HomeField;

class Board : public QWidget
{
    Q_OBJECT

    private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QList<QGraphicsRectItem*> field;
    QList<HomeField*> home;
    void drawSpecial(unsigned index);

    public:
    Board(QWidget *parent = nullptr);
};

#endif

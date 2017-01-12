#ifndef BOARD_HEADER
#define BOARD_HEADER

#include <QWidget>
#include <QList>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
class QGraphicsItemGroup;
class HomeField;

class Board : public QWidget
{
    Q_OBJECT

    private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    // QList<QGraphicsItem*> field;
    QList<HomeField*> home;

    public:
    Board(QWidget *parent = nullptr);
};

#endif

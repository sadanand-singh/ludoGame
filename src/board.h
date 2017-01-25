#ifndef BOARD_HEADER
#define BOARD_HEADER

#include <QWidget>
#include <QList>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsRectItem;
class QGraphicsItemGroup;
class Field;
class HomeField;

class Board : public QWidget
{
    Q_OBJECT

    private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QList<Field*> field;
    QList<HomeField*> home;
    QGraphicsRectItem *diceBox;
    QList<Field*> endField;

    void drawSpecial(unsigned index, QColor color = Qt::darkGray);
    void setupNextField();
    void setupNextSafeZone();

    public:
    explicit Board(QWidget *parent = nullptr);
    QGraphicsScene* getScene();
    QGraphicsRectItem* getDiceBox();
    HomeField* getHome(unsigned color);
};

#endif

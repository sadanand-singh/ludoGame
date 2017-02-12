#ifndef BOARD_HEADER
#define BOARD_HEADER

#include <QWidget>
#include <QList>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsRectItem;
class QGraphicsItemGroup;
class HomeField;
class Field;

class Board : public QWidget
{
    Q_OBJECT

    private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QList<Field*> field;
    QGraphicsRectItem *diceBox;
    QList<Field*> endField;
    QList<HomeField*> home;
    QList<QList<Field*>> startField;

    void drawSpecial(unsigned index, QColor pen = Qt::black);
    void setupNextField();
    void setupNextSafeZone();
    void addStartFields(HomeField *home, unsigned colorIndex, unsigned next);

    public:
    explicit Board(QWidget *parent = nullptr);
    QGraphicsScene* getScene();
    QGraphicsRectItem* getDiceBox();
    QList<Field*>& getStartField(unsigned colorIndex);
    HomeField* getHome(unsigned colorIndex);
};

#endif

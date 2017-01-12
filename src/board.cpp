#include "board.h"
#include "homeField.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QVBoxLayout>
#include <memory>

Board::Board(QWidget *parent) : QWidget(parent),
    scene(nullptr),
    view(nullptr)
{
    view = new QGraphicsView();
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setRenderHint(QPainter::Antialiasing);

    QGraphicsRectItem *rect = scene->addRect(QRectF(0, 0, 600, 600));
    rect->setPen(QPen(Qt::black, 2.0));

    auto redField = std::unique_ptr<HomeField>(new HomeField(0, 0, 0, Qt::red, scene));
    home.append(redField.get());
    auto greenField = std::unique_ptr<HomeField>(new HomeField(360, 0, 90, Qt::green, scene));
    home.append(greenField.get());
    auto yellowField = std::unique_ptr<HomeField>(new HomeField(360, 360, 180, Qt::yellow, scene));
    home.append(yellowField.get());
    auto blueField = std::unique_ptr<HomeField>(new HomeField(0, 360, 270, Qt::blue, scene));
    home.append(blueField.get());

    QGraphicsRectItem *end = scene->addRect(QRectF(240, 240, 120, 120));
    end->setPen(QPen(Qt::black, 2.0));

    auto *vLayout =  new QVBoxLayout();
    this->setLayout(vLayout);
    vLayout->addWidget(view);
}

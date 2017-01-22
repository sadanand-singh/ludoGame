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
    view(nullptr),
    diceBox(nullptr)
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

    // add main field
    for (qreal x = 0; x < 240; x += 40)
    {
        auto box = scene->addRect(x, 240, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    for (qreal y = 200; y >= 0; y -= 40)
    {
        auto box = scene->addRect(240, y, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    auto box1 = scene->addRect(280, 0, 40, 40);
    box1->setPen(QPen(Qt::black, 2.0));
    field.append(box1);
    for (qreal y = 0; y < 240; y += 40)
    {
        auto box = scene->addRect(320, y, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    for (qreal x = 360; x < 600; x += 40)
    {
        auto box = scene->addRect(x, 240, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    auto box2 = scene->addRect(560, 280, 40, 40);
    box2->setPen(QPen(Qt::black, 2.0));
    field.append(box2);
    for (qreal x = 560; x >= 360; x -= 40)
    {
        auto box = scene->addRect(x, 320, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    for (qreal y = 360; y < 600; y += 40)
    {
        auto box = scene->addRect(320, y, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    auto box3 = scene->addRect(280, 560, 40, 40);
    box3->setPen(QPen(Qt::black, 2.0));
    field.append(box3);
    for (qreal y = 560; y >= 360; y -= 40)
    {
        auto box = scene->addRect(240, y, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    for (qreal x = 200; x >= 0; x -= 40)
    {
        auto box = scene->addRect(x, 320, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        field.append(box);
    }
    auto box4 = scene->addRect(0, 280, 40, 40);
    box4->setPen(QPen(Qt::black, 2.0));
    field.append(box4);

    for (qreal x = 40; x < 240; x += 40)
    {
        auto box = scene->addRect(x, 280, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        box->setBrush(QBrush(Qt::red));
        field.append(box);
    }
    for (qreal y = 40; y < 240; y += 40)
    {
        auto box = scene->addRect(280, y, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        box->setBrush(QBrush(Qt::green));
        field.append(box);
    }
    for (qreal x = 520; x >= 360; x -= 40)
    {
        auto box = scene->addRect(x, 280, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        box->setBrush(QBrush(Qt::yellow));
        field.append(box);
    }
    for (qreal y = 360; y < 560; y += 40)
    {
        auto box = scene->addRect(280, y, 40, 40);
        box->setPen(QPen(Qt::black, 2.0));
        box->setBrush(QBrush(Qt::blue));
        field.append(box);
    }

    diceBox = scene->addRect(270, 270, 60, 60);
    diceBox->setVisible(false);

    //special start boxes
    field.at(1)->setBrush(QBrush(Qt::red));
    field.at(14)->setBrush(QBrush(Qt::green));
    field.at(27)->setBrush(QBrush(Qt::yellow));
    field.at(40)->setBrush(QBrush(Qt::blue));

    drawSpecial(1);
    drawSpecial(14);
    drawSpecial(27);
    drawSpecial(40);

    drawSpecial(9, Qt::black);
    drawSpecial(22, Qt::black);
    drawSpecial(35, Qt::black);
    drawSpecial(48, Qt::black);

    auto *vLayout =  new QVBoxLayout();
    this->setLayout(vLayout);
    vLayout->addWidget(view);
}

QGraphicsRectItem* Board::getDiceBox()
{
    return this->diceBox;
}

void Board::drawSpecial(unsigned index, QColor color)
{
    auto brect = field.at(index)->boundingRect();
    auto c = brect.center();
    auto line = scene->addLine(c.x()-8, c.y()-3, c.x()+8, c.y()-3);
    line->setPen(QPen(color, 2.0));
    line = scene->addLine(c.x()+8, c.y()-3, c.x()-5, c.y()+8);
    line->setPen(QPen(color, 2.0));
    line = scene->addLine(c.x()-5, c.y()+8, c.x(), c.y()-8);
    line->setPen(QPen(color, 2.0));
    line = scene->addLine(c.x(), c.y()-8, c.x()+5, c.y()+8);
    line->setPen(QPen(color, 2.0));
    line = scene->addLine(c.x()+5, c.y()+8, c.x()-8, c.y()-3);
    line->setPen(QPen(color, 2.0));
}

QGraphicsScene* Board::getScene()
{
    return this->scene;
}

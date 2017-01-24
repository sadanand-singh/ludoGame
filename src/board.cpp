#include "board.h"
#include "field.h"
#include "lastField.h"
#include "safeField.h"
#include "homeField.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
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

    QGraphicsRectItem *end = scene->addRect(QRectF(240, 240, 120, 120));
    end->setPen(QPen(Qt::black, 2.0));

    // add main field
    for (qreal x = 0; x < 240; x += 40)
    {
        Field* box = new Field(x, 240, 40, 40);
        scene->addItem(box);
        field.append(box);
    }
    for (qreal y = 200; y >= 0; y -= 40)
    {
        Field* box = new Field(240, y, 40, 40);
        scene->addItem(box);
        field.append(box);
    }

    Field* box1 = new LastField(280, 0, 40, 40);
    box1->setColor(Qt::green);
    scene->addItem(box1);
    field.append(box1);

    for (qreal y = 0; y < 240; y += 40)
    {
        Field* box = new Field(320, y, 40, 40);
        scene->addItem(box);
        field.append(box);
    }
    for (qreal x = 360; x < 600; x += 40)
    {
        Field* box = new Field(x, 240, 40, 40);
        scene->addItem(box);
        field.append(box);
    }

    Field* box2 = new LastField(560, 280, 40, 40);
    box2->setColor(Qt::yellow);
    scene->addItem(box2);
    field.append(box2);

    for (qreal x = 560; x >= 360; x -= 40)
    {
        Field* box = new Field(x, 320, 40, 40);
        scene->addItem(box);
        field.append(box);
    }
    for (qreal y = 360; y < 600; y += 40)
    {
        Field* box = new Field(320, y, 40, 40);
        scene->addItem(box);
        field.append(box);
    }

    Field* box3 = new LastField(280, 560, 40, 40);
    box3->setColor(Qt::blue);
    scene->addItem(box3);
    field.append(box3);

    for (qreal y = 560; y >= 360; y -= 40)
    {
        Field* box = new Field(240, y, 40, 40);
        scene->addItem(box);
        field.append(box);
    }
    for (qreal x = 200; x >= 0; x -= 40)
    {
        Field* box = new Field(x, 320, 40, 40);
        scene->addItem(box);
        field.append(box);
    }

    Field* box4 = new LastField(0, 280, 40, 40);
    box4->setColor(Qt::red);
    scene->addItem(box4);
    field.append(box4);

    for (qreal x = 40; x < 240; x += 40)
    {
        Field* box = new SafeField(x, 280, 40, 40);
        scene->addItem(box);
        box->setColor(Qt::red);
        field.append(box);
    }
    for (qreal y = 40; y < 240; y += 40)
    {
        Field* box = new SafeField(280, y, 40, 40);
        scene->addItem(box);
        box->setColor(Qt::green);
        field.append(box);
    }
    for (qreal x = 520; x >= 360; x -= 40)
    {
        Field* box = new SafeField(x, 280, 40, 40);
        scene->addItem(box);
        box->setColor(Qt::yellow);
        field.append(box);
    }
    for (qreal y = 360; y < 560; y += 40)
    {
        Field* box = new SafeField(280, y, 40, 40);
        scene->addItem(box);
        box->setColor(Qt::blue);
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

    setupNextField();
    setupNextSafeZone();

    auto redField = new HomeField(0, 0, 0, Qt::red, scene, this);
    redField->setNextField(field.at(1));
    home.append(redField);
    auto greenField = new HomeField(360, 0, 90, Qt::green, scene, this);
    greenField->setNextField(field.at(14));
    home.append(greenField);
    auto yellowField = new HomeField(360, 360, 180, Qt::yellow, scene, this);
    yellowField->setNextField(field.at(27));
    home.append(yellowField);
    auto blueField = new HomeField(0, 360, 270, Qt::blue, scene, this);
    blueField->setNextField(field.at(40));
    home.append(blueField);

    auto *vLayout =  new QVBoxLayout();
    this->setLayout(vLayout);
    vLayout->addWidget(view);
}

void Board::setupNextField()
{
    QVector<unsigned> ends {56, 61, 66, 71};

    for(auto& box : field)
    {
        auto id = field.indexOf(box);

        // if `id` is not in ends
        if(ends.indexOf(id) == -1)
        {
            id = (id == 51) ? 0 : id + 1;
            box->setNextField(field.at(id));
        }
    }
}

void Board::setupNextSafeZone()
{
    QVector<QPair<unsigned, unsigned>> endSafePairs;
    endSafePairs.append(qMakePair(51, 52));
    endSafePairs.append(qMakePair(12, 57));
    endSafePairs.append(qMakePair(25, 62));
    endSafePairs.append(qMakePair(38, 67));

    for(auto& espair : endSafePairs)
    {
        auto box = field.at(espair.first);
        box->setSafeField(field.at(espair.second));
    }
}

QGraphicsRectItem* Board::getDiceBox()
{
    return this->diceBox;
}

void Board::drawSpecial(unsigned index, QColor color)
{
    auto brect = field.at(index)->boundingRect();
    field.at(index)->makeSpecial();

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

HomeField* Board::getHome(unsigned color)
{
    return home.at(color);
}

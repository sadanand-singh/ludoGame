#include "board.h"
#include "field.h"
#include "startField.h"
#include "lastField.h"
#include "safeField.h"
#include "specialField.h"
#include "homeField.h"
#include "endField.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>

Board::Board(QWidget *parent) : QWidget(parent),
    scene(nullptr),
    view(nullptr),
    diceBox(nullptr)
{
    QList<Field*> fBlank{};
    startField.append(fBlank);
    startField.append(fBlank);
    startField.append(fBlank);
    startField.append(fBlank);

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
    box1->setColor(QColor(85, 107, 47));
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
    box2->setColor(QColor(218, 165, 32));
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
    box3->setColor(QColor(0, 191, 255));
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
    box4->setColor(QColor(205, 92, 92));
    scene->addItem(box4);
    field.append(box4);

    for (qreal x = 40; x < 240; x += 40)
    {
        Field* box = new SafeField(x, 280, 40, 40);
        scene->addItem(box);
        box->setColor(QColor(205, 92, 92));
        field.append(box);
    }
    for (qreal y = 40; y < 240; y += 40)
    {
        Field* box = new SafeField(280, y, 40, 40);
        scene->addItem(box);
        box->setColor(QColor(85, 107, 47));
        field.append(box);
    }
    for (qreal x = 520; x >= 360; x -= 40)
    {
        Field* box = new SafeField(x, 280, 40, 40);
        scene->addItem(box);
        box->setColor(QColor(218, 165, 32));
        field.append(box);
    }
    for (qreal y = 520; y >= 360; y -= 40)
    {
        Field* box = new SafeField(280, y, 40, 40);
        scene->addItem(box);
        box->setColor(QColor(0, 191, 255));
        field.append(box);
    }

    diceBox = scene->addRect(270, 270, 60, 60);
    diceBox->setVisible(false);

    drawSpecial(1);
    drawSpecial(14);
    drawSpecial(27);
    drawSpecial(40);

    drawSpecial(9);
    drawSpecial(22);
    drawSpecial(35);
    drawSpecial(48);

    auto redHome = new HomeField(0, 0, 0, QColor(205, 92, 92), scene, this);
    addStartFields(redHome, 0, 1);
    home.append(redHome);

    auto greenHome = new HomeField(360, 0, 90, QColor(85, 107, 47), scene, this);
    addStartFields(greenHome, 1, 14);
    home.append(greenHome);

    auto yellowHome = new HomeField(360, 360, 180, QColor(218, 165, 32), scene, this);
    addStartFields(yellowHome, 2, 27);
    home.append(yellowHome);

    auto blueHome = new HomeField(0, 360, 270, QColor(0, 191, 255), scene, this);
    addStartFields(blueHome, 3, 40);
    home.append(blueHome);

    // add end Fields
    auto endRed = new EndField(240, 285, 30, 30);
    scene->addItem(endRed);
    endField.append(endRed);

    auto endGreen = new EndField(285, 240, 30, 30);
    scene->addItem(endGreen);
    endField.append(endGreen);

    auto endYellow = new EndField(330, 285, 30, 30);
    scene->addItem(endYellow);
    endField.append(endYellow);

    auto endBlue = new EndField(285, 330, 30, 30);
    scene->addItem(endBlue);
    endField.append(endBlue);

    setupNextField();
    setupPreviousField();
    setupNextSafeZone();

    auto *vLayout =  new QVBoxLayout();
    this->setLayout(vLayout);
    vLayout->addWidget(view);
}

void Board::setupNextField()
{
    QVector<unsigned> ends {56u, 61u, 66u, 71u};

    for (auto& box : field)
    {
        auto id = field.indexOf(box);

        // if `id` is not in ends
        auto endID = ends.indexOf(id);
        if (endID == -1)
        {
            id = (id == 51) ? 0 : id + 1;
            box->setNextField(field[id]);
        }
        else  box->setNextField(endField[endID]);
    }
}

void Board::setupPreviousField()
{
    for (auto& box : field)
    {
        auto id = field.indexOf(box);
        auto prev = id - 1;
        if (prev < 0) prev = 51;

        box->setPreviousField(field[prev]);
    }

}

void Board::addStartFields(HomeField *home, unsigned colorIndex, unsigned next)
{
    auto circles = home->getHomeField();
    auto& starts = startField[colorIndex];
    for (auto& circle : circles)
    {
        auto box = new StartField(circle->boundingRect());
        box->setNextField(field.at(next));
        starts.append(box);
        scene->addItem(box);
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

void Board::drawSpecial(unsigned index, QColor pen)
{
    auto brect = field.at(index)->boundingRect();
    delete field[index];

    auto box = new SpecialField(brect);
    scene->addItem(box);
    field[index] = box;

    auto line = scene->addLine(QLineF(brect.topLeft(), brect.bottomRight()));
    line->setPen(QPen(pen, 2.0));
    line = scene->addLine(QLineF(brect.bottomLeft(), brect.topRight()));
    line->setPen(QPen(pen, 2.0));
}

QGraphicsScene* Board::getScene()
{
    return this->scene;
}

QList<Field*>& Board::getStartField(unsigned colorIndex)
{
    return startField[colorIndex];
}

HomeField* Board::getHome(unsigned colorIndex)
{
    if (colorIndex < 4)
        return home.at(colorIndex);

    return nullptr;
}

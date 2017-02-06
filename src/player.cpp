#include "player.h"
#include "figure.h"
#include "field.h"
#include "homeField.h"
#include <algorithm>

Player::Player(QString n, QColor c, QObject *parent) : QObject(parent),
    homeField(nullptr),
    color(c),
    isActive(false),
    figuresRemaining(4),
    figuresInHouse(4),
    bonusMoves(0),
    name(n)
{}

bool Player::hasWon()
{
    return false;
}

bool Player::hasFigure(Figure *figure)
{
    if (figures.indexOf(figure) == -1)
        return true;

    return true;
}

bool Player::allFiguresInStartHouse()
{
    if (figuresInHouse == 4) return true;
    return false;
}

void Player::setFigures(QList<Figure*> figs)
{
    std::copy(figs.begin(), figs.end(), std::back_inserter(figures));
}

void Player::setHomeField(HomeField* home)
{
    homeField = home;
}

QList<Figure*>& Player::getFigures()
{
    return figures;
}

QList<Field*>& Player::getStartField()
{
    return startField;
}

HomeField* Player::getHomeField()
{
    return homeField;
}

unsigned Player::getFiguresRemaining()
{
    return figuresRemaining;
}

QColor Player::getColor()
{
    return color;
}

QString Player::getName()
{
    return name;
}

void Player::move(Figure *figure)
{
    if (not hasFigure(figure)) return;

    // auto hilight = figure->getHilight();
    // auto pos = figure->getResultPosition();
    // auto scene = pos->scene();
    // scene->removeItem(hilight);
    // delete hilight;
    // hilight = nullptr;

    auto position = figure->getPosition();
    auto newPosition = figure->getResultPosition();

    // find figures at newPosition if not special
    if (not newPosition->isSpecial())
    {
        auto& allFigures = newPosition->getFigures();
        for(auto& fig : allFigures)
        {
            if (fig->getColor() != color)
            {
                fig->moveToHome();
                ++bonusMoves;
            }
            else
            {
                newPosition = nullptr;
                break;
            }
        }
    }

    if (newPosition) figure->setPosition(newPosition);

    // set all other figures to disabled
    for (auto& fig : figures) fig->setEnabled(false);

    // if (hasWon())
    // {
    //     emit gameWon(this);
    //     return;
    // }

    // emit continueGame(nextPlayer);
    // return;
}

void Player::setStartField(QList<Field*>& start)
{
    startField = start;
}

void Player::setDice(unsigned dice)
{
    this->dice = dice;
}

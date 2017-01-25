#include "player.h"
#include "figure.h"
#include "homeField.h"
#include <algorithm>

Player::Player(QString n, QColor c, QObject *parent) : QObject(parent),
    homeField(nullptr),
    color(c),
    isActive(false),
    figuresRemaining(4),
    figuresInHouse(4),
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
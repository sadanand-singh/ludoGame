#include "player.h"
#include "figure.h"
#include "field.h"
#include "endField.h"
#include <algorithm>

Player::Player(QString n, QColor c, QObject *parent) : QObject(parent),
    color(c),
    isActive(false),
    bonusMoves(0),
    name(n)
{}

bool Player::hasWon()
{
    for (auto& fig : figures)
    {
        if(not dynamic_cast<EndField*> (fig->getPosition()))
            return false;
    }
    return true;
}

bool Player::hasFigure(Figure *figure)
{
    if (figures.indexOf(figure) == -1)
        return true;

    return true;
}

void Player::setFigures(QList<Figure*> figs)
{
    std::copy(figs.begin(), figs.end(), std::back_inserter(figures));
}

QList<Figure*>& Player::getFigures()
{
    return figures;
}

QList<Field*>& Player::getStartField()
{
    return startField;
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
    isActive = (bonusMoves > 0);

    // set all other figures to disabled
    for (auto& fig : figures) fig->setEnabled(false);

    auto win = hasWon();
    if (win)
    {
        emit gameWon(win);
        return;
    }

    --bonusMoves;
    if (bonusMoves < 0) bonusMoves = 0;

    emit continueGame(isActive);
    return;
}

void Player::setStartField(QList<Field*>& start)
{
    startField = start;
}

void Player::setDice(unsigned dice)
{
    this->dice = dice;
    if (dice == 6) ++bonusMoves;
}

void Player::setEnabled(bool enable)
{
    isActive = enable;
}

#include "computerPlayer.h"
#include "figure.h"
#include "field.h"
#include "specialField.h"
#include "safeField.h"
#include "startField.h"
#include "endField.h"
#include "game.h"
#include <algorithm>

ComputerPlayer::ComputerPlayer(QString n, QColor c, QObject *parent) :
    Player(n, c, parent)
{}

void ComputerPlayer::setDice(unsigned dice)
{
    this->dice = dice;

    if (isActive)
        play();
}

void ComputerPlayer::play()
{
    QList<Figure*> activeFigures;
    QList<double> costs;

    // find all clickable figures
    for(auto& fig : figures)
        if (fig->isEnabled())
            activeFigures.append(fig);

    if(not activeFigures.size()) return;

    // find cost of moving each of such figures
    for(auto& fig : activeFigures)
        costs.append(moveCost(fig));

    // find minimum cost figure and emit clicked for this
    auto min = std::min_element(costs.begin(), costs.end());
    auto index = std::distance(costs.begin(), min);

    Game::delay(1);
    emit activeFigures.at(index)->clicked(activeFigures.at(index));

    return;
}

double ComputerPlayer::moveCost(Figure* fig)
{
    // find cost of old position
    auto pos = fig->getPosition();
    auto currCost = getFieldCost(pos);

    // find if new field cost
    auto newPos = fig->getResultPosition();
    auto newCost = getFieldCost(newPos);

    auto cost = newCost - currCost;
    return cost;
}

double ComputerPlayer::getFieldCost(Field* pos)
{
    // being in home field has large weigth promoting coming out
    if (dynamic_cast<StartField*>(pos)) return 200.0;

    // if possible do not touch ones in safe field
    if (dynamic_cast<SafeField*>(pos)) return -100.0;
    if (dynamic_cast<EndField*>(pos)) return -50.0;

    // find number of other color, and safe fields behind (6-)
    auto safeBehind = 0u;
    auto othersBehind = 0u;
    auto safeAhead = 0u;
    auto othersAhead = 0u;

    auto prev = pos;
    auto ahead = pos;

    for (auto count = 0u; count < 6u; count++)
    {
        prev = prev->previous();
        if (prev)
        {
            if (prev->isSpecial()) ++safeBehind;
            othersBehind += getOtherCount(prev);
        }

        ahead = ahead->next(color);
        if (ahead)
        {
            if (ahead->isSpecial()) ++safeAhead;
            othersAhead += getOtherCount(ahead, true);
        }
    }

    auto cost = 0.0;
    if (dynamic_cast<SpecialField*>(pos))
    {
        cost -= 100.0;
        cost -= (othersAhead * 20);
        cost += (othersBehind * 5);
        return cost;
    }

    // find if new field is regular field, has other colored figures (kill)
    auto& figs = pos->getFigures();
    if (figs.size() > 0)
    {
        auto otherColor = figs.at(0)->getColor();
        if (otherColor != color) cost -= 500.0;

        // find how far is the othercolor from home
        auto otherColorDistFromHome = distFromHome(pos, otherColor);
        // add more likely to kill the ones too close to safety
        cost -= (otherColorDistFromHome * 2);
    }

    // add a cost of intertia depending on position from home
    auto distanceFromHome = distFromHome(pos, color);
    if (pos->isSpecial())
        cost -= (distanceFromHome * 2);
    else
    {
        if (distanceFromHome > 26)
            cost += (distanceFromHome * 2);
    }

    cost -= (othersAhead * 80);
    cost += (othersBehind * 40);
    cost -= (safeAhead * 50);
    cost += (safeBehind * 10);

    return  cost;
}

unsigned ComputerPlayer::getOtherCount(Field* pos, bool isAhead)
{
    if (isAhead)
    {
        if (dynamic_cast<SpecialField*> (pos))
            return 0;
    }

    auto& figs = pos->getFigures();
    auto countOthers = 0u;
    for (auto& fig : figs)
    {
        auto colorCurrent = fig->getColor();
        if (colorCurrent != color) ++countOthers;
    }
    return countOthers;
}

int ComputerPlayer::distFromHome(Field* pos, QColor colorCurrent)
{
    auto red = QColor(205, 92, 92);
    auto green = QColor(85, 107, 47);
    auto yellow = QColor(218, 165, 32);
    auto blue = QColor(0, 191, 255);

    int homeIndex = 0;
    if (colorCurrent == red) homeIndex = 1;
    if (colorCurrent == green) homeIndex = 14;
    if (colorCurrent == yellow) homeIndex = 27;
    if (colorCurrent == blue) homeIndex = 40;

    auto currentIndex = pos->getIndex();
    if (currentIndex <= 51)
    {
        if (currentIndex >= homeIndex)
            return (currentIndex - homeIndex);
        else
            return (51 + currentIndex - homeIndex);
    }

    return 0;
}

#include "computerPlayer.h"
#include "figure.h"
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
    // find if new field is safe, or end or special
    // find if new field is regular field, has other colored figures (kill)
    // if dice is 6, and piece is in home
    // calculate surrounding behind of new field (6-)
    // calculate surrounding ahead of new field (6+)
    return 0.0;
}

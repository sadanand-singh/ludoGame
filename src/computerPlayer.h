#ifndef COMPUTERPLAYER_HEADER
#define COMPUTERPLAYER_HEADER

#include "player.h"

class Figure;

class ComputerPlayer : public Player
{
    Q_OBJECT

    protected:
    double moveCost(Figure* fig);
    double getFieldCost(Field* pos);
    unsigned getOtherCount(Field* pos, bool isAhead = false);

    public:
    ComputerPlayer(QString name, QColor color, QObject *parent = nullptr);
    void play();

    public slots:
    virtual void setDice(unsigned dice) Q_DECL_OVERRIDE;
};
#endif

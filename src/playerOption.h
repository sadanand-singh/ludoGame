#ifndef PLAYEROPTION_HEADER
#define PLAYEROPTION_HEADER

#include <QWidget>

class PlayerIcon;
class QRadioButton;
class QLineEdit;
class OnDemandSpacer;
class QHBoxLayout;
class QColor;

class PlayerOption : public QWidget
{
    PlayerIcon *icon;
    QRadioButton *computerOption;
    QRadioButton *humanOption;
    QLineEdit *playerName;
    OnDemandSpacer *spacer;
    QHBoxLayout *hLayout;

    public:
    PlayerOption(QColor color, QWidget* parent = nullptr);
    QLineEdit* getPlayerName();
    QRadioButton* getComputerOption();
    QRadioButton* getHumanOption();
};

#endif

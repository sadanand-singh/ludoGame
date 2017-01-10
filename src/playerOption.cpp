#include "playerOption.h"
#include "playerIcon.h"
#include "onDemandSpacer.h"
#include <QRadioButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QColor>

PlayerOption::PlayerOption(QColor color, QWidget* parent) : QWidget( parent),
    icon(new PlayerIcon(color)),
    computerOption(new QRadioButton("Computer")),
    humanOption(new QRadioButton("Human")),
    playerName(new QLineEdit),
    spacer(new OnDemandSpacer),
    hLayout(new QHBoxLayout)
{
    computerOption->setChecked(true);
    humanOption->setChecked(false);

    playerName->setPlaceholderText("Enter player name...");
    playerName->setClearButtonEnabled(true);
    playerName->setVisible(false);
    playerName->setFixedWidth(180);

    spacer->setVisible(true);
    spacer->setFixedWidth(180);

    hLayout->addWidget(icon);
    hLayout->addWidget(computerOption);
    hLayout->addWidget(humanOption);
    hLayout->addWidget(playerName);
    hLayout->addWidget(spacer);

    connect(humanOption, &QRadioButton::toggled, playerName, &QLineEdit::setVisible);
    connect(humanOption, &QRadioButton::toggled, spacer, &QWidget::setHidden);

    this->setLayout(hLayout);
}

QLineEdit* PlayerOption::getPlayerName()
{
    return playerName;
}

QRadioButton* PlayerOption::getComputerOption()
{
    return computerOption;
}

QRadioButton* PlayerOption::getHumanOption()
{
    return humanOption;
}

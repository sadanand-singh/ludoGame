#include "newGameDialog.h"
#include "playerOption.h"
#include "onDemandSpacer.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <QVBoxLayout>
#include <QLineEdit>
#include <set>

NewGameDialog::NewGameDialog(QString title, QDialog* parent) : QDialog(parent),
    vLayout(new QVBoxLayout),
    okButton(new QPushButton(tr("OK"))),
    cancelButton(new QPushButton(tr("Cancel"))),
    spacer(new OnDemandSpacer),
    hLayoutButton(new QHBoxLayout),
    buttons(new QWidget)
{
    playerMap.insert(tr("red"), new PlayerOption(Qt::red));
    playerMap.insert(tr("green"), new PlayerOption(Qt::green));
    playerMap.insert(tr("yellow"), new PlayerOption(Qt::yellow));
    playerMap.insert(tr("blue"), new PlayerOption(Qt::blue));

    vLayout->addWidget(playerMap.value(tr("red")));
    vLayout->addWidget(playerMap.value(tr("green")));
    vLayout->addWidget(playerMap.value(tr("yellow")));
    vLayout->addWidget(playerMap.value(tr("blue")));

    okButton->setEnabled(true);
    okButton->setDefault(true);
    hLayoutButton->addWidget(spacer);
    hLayoutButton->addWidget(okButton);
    hLayoutButton->addWidget(cancelButton);
    buttons->setLayout(hLayoutButton);

    vLayout->addWidget(buttons);
    vLayout->setSizeConstraint(QLayout::SetFixedSize);

    this->setWindowTitle(title);
    this->setLayout(vLayout);
    this->setModal(true);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::close);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    for(auto const& key : playerMap.keys())
    {
        auto field = playerMap.value(key)->getPlayerName();
        connect(field, &QLineEdit::textChanged, this, &NewGameDialog::enableOKButton);

        auto computerOption = playerMap.value(key)->getComputerOption();
        connect(computerOption, &QRadioButton::toggled, this, &NewGameDialog::enableOKButton);
    }
}

void NewGameDialog::enableOKButton()
{
    std::set<QString> playerNames;
    auto nonEmptyNames = 0U;
    auto ok = true;

    for(auto const& key : playerMap.keys())
    {
        auto player = playerMap.value(key);
        auto isHuman = player->getHumanOption()->isChecked();
        auto name = player->getPlayerName()->text();
        auto playerOK = !name.isEmpty() and isHuman;
        if (playerOK) {
            ++nonEmptyNames;
            playerNames.insert(name.toLower());
        }

        playerOK = playerOK or !isHuman;
        ok = ok and playerOK;
    }

    // if more than two texts, disable OK button
    if (nonEmptyNames != playerNames.size())
        ok = false;

    okButton->setEnabled(ok);
}

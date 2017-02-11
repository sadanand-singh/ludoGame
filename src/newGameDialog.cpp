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

NewGameDialog::NewGameDialog(QString title, QWidget* parent) : QDialog(parent),
    vLayout(new QVBoxLayout),
    okButton(new QPushButton(tr("Start Demo"))),
    cancelButton(new QPushButton(tr("Cancel"))),
    spacer(new OnDemandSpacer),
    hLayoutButton(new QHBoxLayout),
    buttons(new QWidget)
{
    playerMap.append(new PlayerOption(Qt::red));
    playerMap.append(new PlayerOption(QColor(85, 107, 47)));
    playerMap.append(new PlayerOption(QColor(218, 165, 32)));
    playerMap.append(new PlayerOption(QColor(147, 112, 219)));

    vLayout->addWidget(playerMap.at(0));
    vLayout->addWidget(playerMap.at(1));
    vLayout->addWidget(playerMap.at(2));
    vLayout->addWidget(playerMap.at(3));

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
    connect(okButton, &QPushButton::clicked, this, &NewGameDialog::savePlayerData);

    for(auto const& player : playerMap)
    {
        auto field = player->getPlayerName();
        connect(field, &QLineEdit::textChanged, this, &NewGameDialog::enableOKButton);

        auto computerOption = player->getComputerOption();
        connect(computerOption, &QRadioButton::toggled, this, &NewGameDialog::enableOKButton);
    }
}

void NewGameDialog::enableOKButton()
{
    std::set<QString> playerNames;
    auto nonEmptyNames = 0U;
    auto ok = true;
    auto anyHuman = false;

    for(auto const& player : playerMap)
    {
        auto isHuman = player->getHumanOption()->isChecked();
        auto name = player->getPlayerName()->text();
        auto playerOK = !name.isEmpty() and isHuman;
        if (playerOK) {
            ++nonEmptyNames;
            playerNames.insert(name.toLower());
        }

        playerOK = playerOK or !isHuman;
        ok = ok and playerOK;
        anyHuman = anyHuman or isHuman;
    }

    // if more than two texts, disable OK button
    if (nonEmptyNames != playerNames.size())
        ok = false;

    auto buttonTitle = tr("Start Demo");
    if (anyHuman) buttonTitle = tr("Start Game");
    okButton->setText(buttonTitle);

    okButton->setEnabled(ok);
}

void NewGameDialog::savePlayerData()
{
    QList<QPair<bool, QString>> playerData;

    for(auto const& player : playerMap)
    {
        auto isHuman = player->getHumanOption()->isChecked();
        auto name = QString("");
        if (isHuman) name = player->getPlayerName()->text();
        playerData.append(qMakePair(isHuman, name));
    }

    this->accept();
    emit startNewGame(playerData);
}

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

    vLayout->addWidget(playerMap["red"]);
    vLayout->addWidget(playerMap["green"]);
    vLayout->addWidget(playerMap["yellow"]);
    vLayout->addWidget(playerMap["blue"]);

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

    auto redField = playerMap["red"]->getPlayerName();
    auto greenField = playerMap["green"]->getPlayerName();
    auto yellowField = playerMap["yellow"]->getPlayerName();
    auto blueField = playerMap["blue"]->getPlayerName();

    connect(redField, &QLineEdit::textChanged, this, &NewGameDialog::enableOKButton);
    connect(greenField, &QLineEdit::textChanged, this, &NewGameDialog::enableOKButton);
    connect(yellowField, &QLineEdit::textChanged, this, &NewGameDialog::enableOKButton);
    connect(blueField, &QLineEdit::textChanged, this, &NewGameDialog::enableOKButton);

    auto redComputerOption = playerMap["red"]->getComputerOption();
    auto greenComputerOption = playerMap["green"]->getComputerOption();
    auto yellowComputerOption = playerMap["yellow"]->getComputerOption();
    auto blueComputerOption = playerMap["blue"]->getComputerOption();

    connect(redComputerOption, &QRadioButton::toggled, this, &NewGameDialog::enableOKButton);
    connect(greenComputerOption, &QRadioButton::toggled, this, &NewGameDialog::enableOKButton);
    connect(yellowComputerOption, &QRadioButton::toggled, this, &NewGameDialog::enableOKButton);
    connect(blueComputerOption, &QRadioButton::toggled, this, &NewGameDialog::enableOKButton);
}

void NewGameDialog::enableOKButton()
{
    auto isRedHuman = playerMap["red"]->getHumanOption()->isChecked();
    auto isGreenHuman = playerMap["green"]->getHumanOption()->isChecked();
    auto isYellownHuman = playerMap["yellow"]->getHumanOption()->isChecked();
    auto isBlueHuman = playerMap["blue"]->getHumanOption()->isChecked();

    std::set<QString> playerNames;
    auto nonEmptyNames = 0U;

    auto redName = playerMap["red"]->getPlayerName()->text();
    auto redOK = !redName.isEmpty() and isRedHuman;
    if (redOK) {
        ++nonEmptyNames;
        playerNames.insert(redName.toLower());
    }

    auto greenName = playerMap["green"]->getPlayerName()->text();
    auto greenOK = !greenName.isEmpty() and isGreenHuman;
    if (greenOK) {
        ++nonEmptyNames;
        playerNames.insert(greenName.toLower());
    }

    auto yellowName = playerMap["yellow"]->getPlayerName()->text();
    auto yellowOK = !yellowName.isEmpty() and isYellownHuman;
    if (yellowOK) {
        ++nonEmptyNames;
        playerNames.insert(yellowName.toLower());
    }

    auto blueName = playerMap["blue"]->getPlayerName()->text();
    auto blueOK = !blueName.isEmpty() and isBlueHuman;
    if (blueOK) {
        ++nonEmptyNames;
        playerNames.insert(blueName.toLower());
    }

    redOK = redOK or !isRedHuman;
    greenOK = greenOK or !isGreenHuman;
    yellowOK = yellowOK or !isYellownHuman;
    blueOK = blueOK or !isBlueHuman;
    auto ok = redOK and greenOK and yellowOK and blueOK;

    // if more than two texts, disable OK button
    if (nonEmptyNames != playerNames.size())
        ok = false;

    okButton->setEnabled(ok);
}

#ifndef NEWGAMEDIALOG_HEADER
#define NEWGAMEDIALOG_HEADER

#include <QDialog>
#include <QList>
#include <QPair>

class PlayerOption;
class QString;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class OnDemandSpacer;

class NewGameDialog : public QDialog
{
    Q_OBJECT

    private:
    QList<PlayerOption*> playerMap;
    QVBoxLayout *vLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    OnDemandSpacer *spacer;
    QHBoxLayout *hLayoutButton;
    QWidget *buttons;

    private slots:
    void enableOKButton();
    void savePlayerData();

    signals:
    void startNewGame(const QList<QPair<bool, QString>> data);

    public:
    NewGameDialog(QString title, QWidget* parent = nullptr);
};

#endif

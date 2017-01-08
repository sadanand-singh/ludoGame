#ifndef NEWGAMEDIALOG_HEADER
#define NEWGAMEDIALOG_HEADER

#include <QDialog>
#include <QMap>

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
    QMap<QString, PlayerOption*> playerMap;
    QVBoxLayout *vLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    OnDemandSpacer *spacer;
    QHBoxLayout *hLayoutButton;
    QWidget *buttons;

    private slots:
    void enableOKButton();

    public:
    NewGameDialog(QString title, QDialog* parent = nullptr);
};

#endif

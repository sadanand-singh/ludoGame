#include <QApplication>
#include "newGameDialog.h"

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    NewGameDialog *dialog = new NewGameDialog("Choices...");
    dialog->show();

    return app.exec();
}

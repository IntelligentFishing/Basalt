#include <QtWidgets/QApplication>

#include "mainwindow.h"

int main(int argc, char **argv)
{
    //Q_INIT_RESOURCE(queries);
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}

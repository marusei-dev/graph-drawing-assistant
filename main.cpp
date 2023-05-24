#include "mainwindow.h"
#include <QApplication>

/*
 * The place where the code starts to be executed. Being the main function of the programme, int main() does not contain much code, it's sole purpose
 * is to launch the application and show the main window.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}

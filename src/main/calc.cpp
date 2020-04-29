#include <QtWidgets/QApplication>
#include "qt/mainwindow.h"

/**
 * Starts the main application loop and displays main window
 */
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}

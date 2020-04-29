#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QCloseEvent>
#include "manualwindow.h"
#include "ui_manualwindow.h"

/**
 * Sets up a window for displaying user manual
 * @param parent parent widget
 */
ManualWindow::ManualWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManualWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/fitutubies-calculator.png"));
    readSettings();
    ui->webBrowser->setUrl(QUrl("qrc:/userManual.html"));
}

ManualWindow::~ManualWindow()
{
    delete ui;
}

/**
 * Closes the user manual window and saves its size and position into a config file
 * @param event event to be closed
 */
void ManualWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("fitutubies", "calculator");
    settings.setValue(this->objectName()+"/geometry", saveGeometry());
    settings.setValue(this->objectName()+"/windowState", saveState());
    event->accept();
}

/**
 * Loads the window size and position of user manual window from a config file
 */
void ManualWindow::readSettings()
{
    QSettings settings("fitutubies", "calculator");
    restoreGeometry(settings.value(this->objectName()+"/geometry").toByteArray());
    restoreState(settings.value(this->objectName()+"/windowState").toByteArray());
}

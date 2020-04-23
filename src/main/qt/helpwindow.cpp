#include <QtCore/QSettings>
#include <QtCore/QFile>
#include <QCloseEvent>
#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    readSettings();
    ui->webBrowser->setUrl(QUrl("qrc:/userHelp.html"));
}

HelpWindow::~HelpWindow()
{
    delete ui;
}

void HelpWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("fitutubies", "calculator");
    settings.setValue(this->objectName()+"/geometry", saveGeometry());
    settings.setValue(this->objectName()+"/windowState", saveState());
    event->accept();
}

void HelpWindow::readSettings()
{
    QSettings settings("fitutubies", "calculator");
    restoreGeometry(settings.value(this->objectName()+"/geometry").toByteArray());
    restoreState(settings.value(this->objectName()+"/windowState").toByteArray());
}

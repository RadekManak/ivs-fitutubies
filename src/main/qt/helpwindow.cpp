#include <QtCore/QSettings>
#include <QtCore/QFile>
#include "helpwindow.h"
#include "ui_helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
    readSettings();
    QFile css(":/userHelp.css");
    css.open(QIODevice::ReadOnly);
    QFile html(":/userHelp.html");
    html.open(QIODevice::ReadOnly);
    ui->textBrowser->setStyleSheet(css.readAll());
    ui->textBrowser->setHtml(html.readAll());
    css.close();
    html.close();
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
    this->hide();
}

void HelpWindow::readSettings()
{
    QSettings settings("fitutubies", "calculator");
    restoreGeometry(settings.value(this->objectName()+"/geometry").toByteArray());
    restoreState(settings.value(this->objectName()+"/windowState").toByteArray());
}

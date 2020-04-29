#include <QtCore/QSettings>
#include <QtCore/QPointer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

#include "calclib/calclib.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/fitutubies-calculator.png"));
    readSettings();

    // Menubar
    connect(ui->actionUser_Help, &QAction::triggered, this, &MainWindow::displayUserManual);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    //action buttons
    connect(ui->pushButton_c, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->pushButton_equals, &QPushButton::clicked, this, &MainWindow::calculate);

    //numbers displayed
    connect(ui->pushButton_0, &QPushButton::clicked, this, [=](){number_pressed("0");});
    connect(ui->pushButton_1, &QPushButton::clicked, this, [=](){number_pressed("1");});
    connect(ui->pushButton_2, &QPushButton::clicked, this, [=](){number_pressed("2");});
    connect(ui->pushButton_3, &QPushButton::clicked, this, [=](){number_pressed("3");});
    connect(ui->pushButton_4, &QPushButton::clicked, this, [=](){number_pressed("4");});
    connect(ui->pushButton_5, &QPushButton::clicked, this, [=](){number_pressed("5");});
    connect(ui->pushButton_6, &QPushButton::clicked, this, [=](){number_pressed("6");});
    connect(ui->pushButton_7, &QPushButton::clicked, this, [=](){number_pressed("7");});
    connect(ui->pushButton_8, &QPushButton::clicked, this, [=](){number_pressed("8");});
    connect(ui->pushButton_9, &QPushButton::clicked, this, [=](){number_pressed("9");});

    //arithmetic symbols
    connect(ui->pushButton_addition, &QPushButton::clicked, this, [=](){number_pressed("+");});
    connect(ui->pushButton_subtraction, &QPushButton::clicked, this, [=](){number_pressed("-");});
    connect(ui->pushButton_mulitplication, &QPushButton::clicked, this, [=](){number_pressed("*");});
    connect(ui->pushButton_division, &QPushButton::clicked, this, [=](){number_pressed("/");});
    connect(ui->pushButton_log, &QPushButton::clicked, this, [=](){number_pressed("log(");});

    //goniometric funcions
    connect(ui->pushButton_cos, &QPushButton::clicked, this, [=](){number_pressed("cos(");});
    connect(ui->pushButton_sin, &QPushButton::clicked, this, [=](){number_pressed("sin(");});
    connect(ui->pushButton_tan, &QPushButton::clicked, this, [=](){number_pressed("tan(");});

    //modulus
    connect(ui->pushButton_modulus, &QPushButton::clicked, this, [=](){number_pressed("%");});

    //factorial
    connect(ui->pushButton_factorial, &QPushButton::clicked, this, [=](){number_pressed("!");});

    //decimal point
    connect(ui->pushButton_point, &QPushButton::clicked, this, [=](){number_pressed(".");});

    //Brackets
    connect(ui->pushButton_lbr, &QPushButton::clicked, this, [=](){number_pressed("(");});
    connect(ui->pushButton_rbr, &QPushButton::clicked, this, [=](){number_pressed(")");});
    connect(ui->pushButton_colon, &QPushButton::clicked, this, [=](){number_pressed(":");});

    //decimal point
    connect(ui->pushButton_point, &QPushButton::clicked, [=](){ ui->pushButton_point->animateClick();});

    //square root
    connect(ui->pushButton_sqrt, &QPushButton::clicked, this, [=](){number_pressed("root(");});

    //constants
    connect(ui->pushButton_e, &QPushButton::clicked, this, [=](){number_pressed("e");});
    connect(ui->pushButton_pi, &QPushButton::clicked, this, [=](){number_pressed("pi");});

    //exponent
    connect(ui->pushButton_power, &QPushButton::clicked, this, [=](){number_pressed("^");});

    auto calculateAction = new QAction(this);
    calculateAction->setShortcuts({tr("Enter"), tr("Return") });
    this->addAction(calculateAction);
    connect(calculateAction, &QAction::triggered,this,  &MainWindow::calculate);

    ui->outputLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if (!ui->inputLine->hasFocus() && e->text() != " " && e->text() != "" && e->text().data()->isPrint()){
        std::cout << ">" << e->text().toStdString() << "<";
        number_pressed(e->text());
    }
}

void MainWindow::number_pressed(const QString &value) {
    ui->inputLine->setFocus();
    int tc = ui->inputLine->cursorPosition();
    ui->inputLine->setText(ui->inputLine->text().insert(tc, value));
    ui->inputLine->setCursorPosition(tc + value.length());
}

void MainWindow::clear() {
    ui->inputLine->clear();
    ui->inputLine->setFocus();
}

void MainWindow::calculate() {
    ui->outputLabel->setText(QString::fromStdString(calc.solveEquation(ui->inputLine->text().toStdString())));
    ui->inputLine->setFocus();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("fitutubies", "calculator");
    settings.setValue(this->objectName()+"/geometry", saveGeometry());
    settings.setValue(this->objectName()+"/windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::readSettings()
{
    QSettings settings("fitutubies", "calculator");
    restoreGeometry(settings.value(this->objectName()+"/geometry").toByteArray());
    restoreState(settings.value(this->objectName()+"/windowState").toByteArray());
}

void MainWindow::displayUserManual()
{
    static QPointer<ManualWindow> manualWindow;
    if (!manualWindow) {
        manualWindow = new ManualWindow();
        manualWindow->setAttribute(Qt::WA_DeleteOnClose);
    }
    manualWindow->show();
    manualWindow->raise();
}

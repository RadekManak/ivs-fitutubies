#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "calclib/calclib.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("0");
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
    connect(ui->pushButton_c, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->pushButton_ac, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->pushButton_addition, &QPushButton::clicked, this, [=](){number_pressed("+");});
    connect(ui->pushButton_subtraction, &QPushButton::clicked, this, [=](){number_pressed("-");});
    connect(ui->pushButton_mulitplication, &QPushButton::clicked, this, [=](){number_pressed("*");});
    connect(ui->pushButton_division, &QPushButton::clicked, this, [=](){number_pressed("/");});
    connect(ui->pushButton_equals, &QPushButton::clicked, this, &MainWindow::calculate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::number_pressed(const QString &value) {
    if (ui->label->text() == "0"){
        ui->label->setText(value);
        return;
    }
    ui->label->setText(ui->label->text() + value);
}

void MainWindow::clear() {
    ui->label->setText("0");
}

void MainWindow::calculate() {
    ui->label->setText(QString::number(calcLib::solveEquation(ui->label->text().toStdString())));
}

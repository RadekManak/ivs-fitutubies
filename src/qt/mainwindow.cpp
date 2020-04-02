#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "calclib/calclib.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("0");

    //action buttons
    connect(ui->pushButton_c, &QPushButton::clicked, this, &MainWindow::clear);
    connect(ui->pushButton_ac, &QPushButton::clicked, this, &MainWindow::clear);
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
    connect(ui->pushButton_log, &QPushButton::clicked, this, [=](){number_pressed("log");});

    //goniometric funcions
    connect(ui->pushButton_cos, &QPushButton::clicked, this, [=](){number_pressed("cos");});
    connect(ui->pushButton_sin, &QPushButton::clicked, this, [=](){number_pressed("sin");});
    connect(ui->pushButton_tan, &QPushButton::clicked, this, [=](){number_pressed("tan");});

    //modulus
    connect(ui->pushButton_modulus, &QPushButton::clicked, this, [=](){number_pressed("%");});

    //factorial
    connect(ui->pushButton_factorial, &QPushButton::clicked, this, [=](){number_pressed("!");});

    //decimal point
    connect(ui->pushButton_point, &QPushButton::clicked, this, [=](){number_pressed(",");});

    //square root
    connect(ui->pushButton_sqrt, &QPushButton::clicked, this, [=](){number_pressed("√");});

    //constants
    connect(ui->pushButton_e, &QPushButton::clicked, this, [=](){number_pressed("e");});
    connect(ui->pushButton_pi, &QPushButton::clicked, this, [=](){number_pressed("π");});

    //square
    connect(ui->pushButton_square, &QPushButton::clicked, this, [=](){number_pressed("²");});

    //exponent
    connect(ui->pushButton_power, &QPushButton::clicked, this, [=](){number_pressed("^");});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::number_pressed(const QString &value) {
    if (new_expression){ // Clear result
        ui->label->setText(value);
        new_expression = false;
        return;
    }
    ui->label->setText(ui->label->text() + value);
}



void MainWindow::clear() {
    ui->label->setText("0");
    new_expression = true;
}

void MainWindow::calculate() {
    ui->label->setText(QString::fromStdString(calcLib::solveEquation(ui->label->text().toStdString())));
    new_expression = true;
}

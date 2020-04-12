#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "calclib/calclib.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    auto action = new QAction(this);
    action->setShortcuts({ tr(","), tr(".") });
    this->addAction(action);
    connect(action, &QAction::triggered, [=](){ ui->pushButton_point->animateClick();});
    
    //square root
    connect(ui->pushButton_sqrt, &QPushButton::clicked, this, [=](){number_pressed("root(");});

    //constants
    connect(ui->pushButton_e, &QPushButton::clicked, this, [=](){number_pressed("e");});
    connect(ui->pushButton_pi, &QPushButton::clicked, this, [=](){number_pressed("pi");});

    //exponent
    connect(ui->pushButton_power, &QPushButton::clicked, this, [=](){number_pressed("^");});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::number_pressed(const QString &value) {
    if (new_expression){ // Clear result
        ui->inputLine->setText(value);
        new_expression = false;
        return;
    }
    ui->inputLine->setText(ui->inputLine->text() + value);
}



void MainWindow::clear() {
    ui->inputLine->setText("0");
    new_expression = true;
}

void MainWindow::calculate() {
    ui->outputLabel->setText(QString::fromStdString(calc.solveEquation(ui->inputLine->text().toStdString())));
    new_expression = true;
}

//void MainWindow::on_actionDisplay_guide_triggered()
//{
//    QTextEdit* message = new QTextEdit();
//    message->setWindowFlags(Qt::Window);
//    message->setReadOnly(true);
//    message->append("Here goes the user guide.");
//    message->show();
//}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionDisplay_user_guide_triggered()
{
    QTextEdit* message = new QTextEdit();
    message->setWindowFlags(Qt::Window);
    message->setWindowTitle("User Guide");
    message->setReadOnly(true);
    message->append("-----User guide");
    //message->show();
    message->append("Use this calculator in order to perform basic, or slightly advanced mathematical calculations.\n\n");
    message->append("-----Type numbers");
    message->append("In order to express values simply press the numerical ‘0’ to ‘9’ buttons to display necessary digits.\n\n");
    message->append("-----Go decimal");
    message->append("Make sure to use ‘.’ to separate mantissa and the exponent, in order to work with decimal numbers.\n\n");
    message->append("-----Use constants");
    message->append("There is no need to remember endless constants since this calculator has them ready for you. In order to work with Pi press ‘π’ and ‘e’ for Euler’s number.\n\n");
    message->append("-----Perform operations");
    message->append("In order to make use of calculator’s full potential, you can employ a variety of operations, ranging from arithmetic, goniometric, to logarithmic ones. Insert appropriate symbol between the values to  accomplish a desired operation.\n\n");
    message->append("-----Separate the expressions");
    message->append("When working with advanced operations, it is necessary to separate the arguments. Follow the example root(power:base) .\n\n");
    message->append("-----Adjust priority");
    message->append("In order to ensure proper priority of individual sub-expressions, surround them using the bracket buttons. Use ‘(’ at the beginning of an expression and ‘)’ at the end of it. \n\n");
    message->append("-----Correct mistakes");
    message->append("Any typos, incorrect numbers or previous results can be easily corrected. In order to make the display clear, press the ‘C’ button.\n\n");
    message->append("-----Get the result");
    message->append("The result of entered expression can be calculated and displayed using the ‘=’ button.\n\n");
    message->append("For any further information please refer to User manual for Fitutubies calculator");

    message->show();
}

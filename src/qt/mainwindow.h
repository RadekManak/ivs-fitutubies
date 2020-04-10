#pragma once

#include <QMainWindow>
#include "include/calclib/calclib.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool new_expression = true;
    calcLib calc;

private:
    Ui::MainWindow *ui;

public slots:
    void number_pressed(const QString &value);
    void clear();
    void calculate();
};

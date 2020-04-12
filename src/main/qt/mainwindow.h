#pragma once

#include <QMainWindow>
#include "include/calclib/calclib.hpp"

#include <QTextEdit>

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
private slots:
    void on_actionExit_triggered();
    void on_actionDisplay_user_guide_triggered();
};

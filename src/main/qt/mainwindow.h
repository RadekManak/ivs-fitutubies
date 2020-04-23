#pragma once

#include <QMainWindow>
#include "helpwindow.h"
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
    calcLib calc;

private:
    Ui::MainWindow *ui;
    HelpWindow* helpWindow;

public slots:
    void keyPressEvent(QKeyEvent *e);
    void number_pressed(const QString &value);
    void clear();
    void calculate();
private slots:
    void displayUserGuide();

    void readSettings();

    void closeEvent(QCloseEvent *event);
};

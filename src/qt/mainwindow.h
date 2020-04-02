#pragma once

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

public slots:
    void display_symbol(const QString &value);
    void clear();
    void calculate();
};

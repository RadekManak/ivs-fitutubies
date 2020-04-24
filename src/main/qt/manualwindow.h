#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>

namespace Ui {
class ManualWindow;
}

class ManualWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManualWindow(QWidget *parent = nullptr);
    ~ManualWindow();

private:
    Ui::ManualWindow *ui;

    void closeEvent(QCloseEvent *event);

    void readSettings();
};

#endif // HELPWINDOW_H

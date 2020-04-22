#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QMainWindow>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr);
    ~HelpWindow();

private:
    Ui::HelpWindow *ui;

    void closeEvent(QCloseEvent *event);

    void readSettings();
};

#endif // HELPWINDOW_H

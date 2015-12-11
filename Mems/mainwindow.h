#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dlgrs.h>
#include <viewport.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DlgRs* dlgRS;
    ViewPort* vPort;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

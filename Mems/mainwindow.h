#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dlgrs.h>
#include <viewport.h>
#include <parsdata.h>

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
    ParsData *pars;
    int viewInt;

    QByteArray data;

public slots:
    void getData(QByteArray bA);
private slots:
    void on_actionTerminal_triggered();

    void on_actionWriteLog_triggered();

    void getParsDataMems(FormatMsg::DataMems dan);
    void getParsDataMemsList(QList<FormatMsg::DataMems> listMsg);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

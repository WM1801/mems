#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //dlgRS = new DlgRs(this);
    //dlgRS->show();
    vPort = new ViewPort();
    vPort->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

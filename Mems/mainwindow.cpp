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
    connect(vPort, SIGNAL(newData(QByteArray)),
            this, SLOT(getData(QByteArray)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getData(QByteArray bA)
{
    qDebug()<< bA.toHex();
}

void MainWindow::on_actionTerminal_triggered()
{
    if(vPort->isVisible())
    {
        vPort->hide();
    }
    else
    {
        vPort->show();
    }
}

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

    pars = new ParsData();

    connect(pars, SIGNAL(newDataMems(FormatMsg::DataMems)),
            this, SLOT(getParsDataMems(FormatMsg::DataMems)));
    connect(pars, SIGNAL(newDataMemsList(QList<FormatMsg::DataMems>)),
            this, SLOT(getParsDataMemsList(QList<FormatMsg::DataMems>)));
   viewInt = 0;

}

MainWindow::~MainWindow()
{

    delete ui;
}
// принятые данные из RS
void MainWindow::getData(QByteArray bA)
{

    data.append(bA);
  // qDebug()<< data.toHex();
    // отправлены на декодирование
    pars->parsComList(data);
    data.clear();
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

void MainWindow::on_actionWriteLog_triggered()
{

}

void MainWindow::getParsDataMems(FormatMsg::DataMems dan)
{
    qDebug()<< "modul =" << dan.numberMod
    << "count = " << dan.count
    << "Xg = " << dan.Xg;
}

void MainWindow::getParsDataMemsList(QList<FormatMsg::DataMems> listMsg)
{
    if(listMsg.size()>0)
    {
        viewInt++;
        if(viewInt>100)
        {
        qDebug()<< "1 msg iz 100: modul =" << listMsg.at(0).numberMod
        << " count =" << listMsg.at(0).count
        << " Xa=" << listMsg.at(0).Xa
        << " Ya=" << listMsg.at(0).Ya
        << " Za=" << listMsg.at(0).Za
        << " Xg=" << listMsg.at(0).Xg
        << " Yg=" << listMsg.at(0).Yg
        << " Zg=" << listMsg.at(0).Zg
        << " Ta=" << listMsg.at(0).Ta
        << " Tg=" << listMsg.at(0).Tg;
        viewInt = 0;
        }
        listMsg.clear();

    }
}

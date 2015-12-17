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

   //log
   lgMems = new LogMems();
   enabWriteLog = false;
   maxRecordValue = 0;
   currentRecordValue = 0;
   connect(lgMems, SIGNAL(sPressEnabLog(bool, int)),
           this, SLOT(startEndWriteLog(bool, int )));
   connect(lgMems, SIGNAL(sPressViewFile()),
           this, SLOT(startViewFileLog()));

    clbrAcc = new CalibrAcc();
    bClbrAcc = false;
    connect(clbrAcc, SIGNAL(startReadData(bool)),
            this, SLOT(getStateClbrAcc(bool)));



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
    if(lgMems->isVisible())
    {
        lgMems->hide();
    }
    else
    {
        lgMems->show();
    }
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
        // write log
        if(enabWriteLog)
        {
            if(currentRecordValue == 0)
            {
                wFile.createFile(" modul" + listMsg.at(0).numberMod);
                wFile.addStr("# Xa Ya Za Xg Yg Zg");
            }
            foreach (FormatMsg::DataMems dM, listMsg) {
                if(currentRecordValue<maxRecordValue)
                {
                    currentRecordValue++;
                    QString s = "  ";
                   QByteArray str;
                   str.append(QString::number(currentRecordValue, 10));
                   //str.append(s);
                   //str.append(QString::number(dM.count, 10));
                   str.append(s);
                   str.append(QString::number(dM.Xa, 10));
                   str.append(s);
                   str.append(QString::number(dM.Ya, 10));
                   str.append(s);
                   str.append(QString::number(dM.Za, 10));
                   str.append(s);
                   str.append(QString::number(dM.Xg, 10));
                   str.append(s);
                   str.append(QString::number(dM.Yg, 10));
                   str.append(s);
                   str.append(QString::number(dM.Zg, 10));
                    wFile.addStr(str);
                    lgMems->setProgressBarLog(currentRecordValue*100/maxRecordValue);
                }
            }


        }
        // calibr Acc
        if(bClbrAcc)
        {
            foreach (FormatMsg::DataMems dM, listMsg) {
                clbrAcc->getData(dM);
            }

        }

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

void MainWindow::startEndWriteLog(bool b, int n)
{
    if(b)
    {
        lgMems->setProgressBarLog(0);
        enabWriteLog = true;
        maxRecordValue = n;
        currentRecordValue = 0;

    }
    else
    {
        QString s = wFile.getNameFile();
        wFile.closeFile(s);
         enabWriteLog = false;
         currentRecordValue = 0;
    }
}

void MainWindow::startViewFileLog()
{
    QString name = wFile.getNameFile();
    wFile.closeFile(name);
    wFile.viewFile(name);
}

void MainWindow::on_actionCalibrovka_ACC_triggered()
{
    if(clbrAcc->isVisible())
    {
        clbrAcc->hide();
    }
    else
    {
        clbrAcc->show();
    }
}

void MainWindow::getStateClbrAcc(bool b)
{
    bClbrAcc = b;
}

#include "logmems.h"
#include "ui_logmems.h"

LogMems::LogMems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogMems)
{
    ui->setupUi(this);
    enabLog = false;
    setProgressBarLog(0);

    connect(ui->btEnabWriteLog, SIGNAL(released()),
            this, SLOT(pressEnLog()));
    connect(ui->btOpenFile, SIGNAL(released()),
            this, SLOT(pressViewFile()));
}

LogMems::~LogMems()
{
    delete ui;
}

void LogMems::setProgressBarLog(int n)
{
    ui->pBLog->setValue(n);
    if(n==100)
    {
        pressEnLog();
    }
}

void LogMems::pressEnLog()
{
    enabLog = !enabLog;
    int n = getNumbRecord();
    if(enabLog)
    {

        if(n>0)
        {
            ui->btEnabWriteLog->setText("Disable write");
        }

    }
    else
    {
         ui->btEnabWriteLog->setText("Enable write");
    }
    sPressEnabLog(enabLog, n);
}

void LogMems::pressViewFile()
{
    emit sPressViewFile();
}

int LogMems::getNumbRecord()
{
    bool b;
    QString s = ui->leNumbersRecords->text();
    int n = s.toInt(&b, 10);
    if(b)
    {
        //emit sGetNumbersRecords(n);
    }
    else
    {
        ui->leNumbersRecords->clear();
        n = 0;
    }
    return n;

}

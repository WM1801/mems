#include "viewport.h"
#include "ui_viewport.h"

ViewPort::ViewPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewPort)
{
    ui->setupUi(this);


    initDlgText();
    initSerilaPort();
    updateSetting(0);

    bOpenPort = false;
    bEnabViewText = true;
    bHexView = false;
    ui->checkViewData->setChecked(bEnabViewText);
    connect(ui->checkViewData, SIGNAL(clicked(bool)),
            this, SLOT(initChechBoxView(bool)));
    ui->checkHexView->setChecked(bHexView);
    connect(ui->checkHexView, SIGNAL(clicked(bool)),
            this, SLOT(setHexView(bool)));


    connect(ui->btFindPort, SIGNAL(clicked()),
            this, SLOT(findPort()));
    connect(ui->btOpenPort, SIGNAL(clicked(bool)),
            this, SLOT(openClosePort()));

    connect(ui->comboPortRs, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSetting(int)));
    connect(ui->comboBaudRate, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSetting(int)));
    connect(ui->comboDataBits, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSetting(int)));
    connect(ui->comboFlowCtrl, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSetting(int)));
    connect(ui->comboParity, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSetting(int)));
    connect(ui->comboStopBits, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateSetting(int)));



    thread->start();

}


ViewPort::~ViewPort()
{
    delete ui;
}


void ViewPort::initDlgText()
{
    ui->comboBaudRate->addItem("9600", QSerialPort::Baud9600);
    ui->comboBaudRate->addItem("19200", QSerialPort::Baud19200);
    ui->comboBaudRate->addItem("38400", QSerialPort::Baud38400);
    ui->comboBaudRate->addItem("57600", QSerialPort::Baud57600);
    ui->comboBaudRate->addItem("115200", QSerialPort::Baud115200);
    ui->comboBaudRate->addItem("230400", 230400);
    ui->comboBaudRate->addItem("460800", 460800);
    ui->comboBaudRate->addItem("921600", 921600);

    ui->comboDataBits->addItem("8", QSerialPort::Data8);
    ui->comboDataBits->addItem("7", QSerialPort::Data7);
    ui->comboDataBits->addItem("6", QSerialPort::Data6);
    ui->comboDataBits->addItem("5", QSerialPort::Data5);

    ui->comboParity->addItem("None", QSerialPort::NoParity);
    ui->comboParity->addItem("Odd", QSerialPort::EvenParity);
    ui->comboParity->addItem("Even", QSerialPort::OddParity);
    ui->comboParity->addItem("Mark", QSerialPort::MarkParity);
    ui->comboParity->addItem("Space", QSerialPort::SpaceParity);

    ui->comboStopBits->addItem("1", QSerialPort::OneStop);
    ui->comboStopBits->addItem("2", QSerialPort::TwoStop);

    ui->comboFlowCtrl->addItem("None", QSerialPort::NoFlowControl);
    ui->comboFlowCtrl->addItem("RTS/CTS", QSerialPort::HardwareControl);
    ui->comboFlowCtrl->addItem("XON/XOFF", QSerialPort::SoftwareControl);

    findPort();



}

void ViewPort::updateSetting(int n)
{
    bool b;
    if(bOpenPort)
    {
        openClosePort();
    }
        currentSetting.name = ui->comboPortRs->currentText();
        //baudrate
        currentSetting.baudRate = ui->comboBaudRate->currentText().toInt(&b, 0);
        //currentSetting.strBaudRate = ui->comboBaudRate->currentText();
        // DataBits
        currentSetting.dataBits = static_cast<QSerialPort::DataBits>(
                    ui->comboDataBits->itemData(ui->comboDataBits->currentIndex()).toInt());
        //currentSetting.strDataBits = ui->comboDataBits->currentText();
        //Parity
        currentSetting.parity = static_cast<QSerialPort::Parity>(
                        ui->comboParity->itemData(ui->comboParity->currentIndex()).toInt());
        //currentSetting.strParity = ui->comboParity->currentText();
        //Stop bits
        currentSetting.stopBits = static_cast<QSerialPort::StopBits>(
                    ui->comboStopBits->itemData(ui->comboStopBits->currentIndex()).toInt());
        //currentSetting.strStopBits = ui->comboStopBits->currentText();
        //Flow control
        currentSetting.flowControl = static_cast<QSerialPort::FlowControl>(
                    ui->comboFlowCtrl->itemData(ui->comboFlowCtrl->currentIndex()).toInt());
        //currentSetting.strFlowControl = ui->comboFlowCtrl->currentText();
        //Additional options
        //currentSetting.localEchoEnabled = false;
        //emit nMy::SettingPort(currentSetting);
       // port->setMy::SettingPort(currentSetting);

}

QStringList ViewPort::selectPort()
{
    QStringList list;
   foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
      list << info.portName();
   }
   return list;
}

void ViewPort::findPort()
{
    ui->comboPortRs->clear();
    QStringList ls = selectPort();

    if((ls.size()==0))
    {
        QMessageBox::critical(this,tr("Error") ,tr("Not find COM-port"));
        bOpenPort = false;
        ui->btOpenPort->setText("Open");
    }
    else
    {

         foreach(QString str, ls)
         {
            ui->comboPortRs->addItem(str);
         }
        ui->comboPortRs->setCurrentIndex(ls.size()-1);
    }
    ls.clear();

}

void ViewPort::initChechBoxView(bool b)
{
    bEnabViewText = b;
}

void ViewPort::initSerilaPort()
{
    bOpenPort = false;
    port = new Port();
    thread = new QThread();
    port->moveToThread(thread);
    port->serial.moveToThread(thread);

    qRegisterMetaType<My::SettingPort>("My::SettingPort");

    connect(port,SIGNAL(error(QString)),
            this, SLOT(getMsg(QString)));
    connect(port, SIGNAL(outPort(QByteArray)),
            this, SLOT(getData(QByteArray)));
    connect(this, SIGNAL(sOpenPort()),
            port, SLOT(connectPort()));
    connect(this, SIGNAL(sClosePort()),
            port, SLOT(disconnectPort()));
    connect(this, SIGNAL(nSettingPort(My::SettingPort)),
            port,SLOT(setSettingPort(My::SettingPort)));

}

Port::Settings ViewPort::getSetting()
{
    return currentSetting;
}



void ViewPort::openClosePort()
{

    if(bOpenPort)//port open -> close
    {

        emit sClosePort();
        //port->disconnectPort();
        ui->btOpenPort->setText("Open");
        bOpenPort = false;
    }
    else // port close -> open
    {
       //port->setMy::SettingPort(getSetting());
       //port->connectPort();
        Port::Settings s = getSetting();
        My::SettingPort d;
        d.name = s.name;
        d.baudRate = s.baudRate;
        d.dataBits = s.dataBits;
        d.flowControl = s.flowControl;
        d.parity = s.parity;
        d.stopBits = s.stopBits;
       emit nSettingPort(d);
       emit sOpenPort();
       ui->btOpenPort->setText("Close");
       bOpenPort = true;
    }

    if(port->getIsOpenPort())
    {
        ui->plainConsole->setEnabled(false);
    }
    else
    {
        ui->plainConsole->setEnabled(true);
    }

}



void ViewPort::addTextConsole(QByteArray s, bool PrmWrt)
{
    if(bEnabViewText)
    {
        if(PrmWrt)
        {

            ui->plainConsole->insertStrokuQByteArray2(s, "white", bHexView);


        }
        else
        {
            ui->plainConsole->insertStrokuQByteArray2(s, "green", bHexView);
        }
    }
}

void ViewPort::getData(QByteArray bA)
{
    //qDebug() << "data in";
    QByteArray data = bA;

    addTextConsole(bA, true);
    newData(data);
    data.clear();
}

void ViewPort::writeData(QByteArray b)
{
    QByteArray data = b;
    writeData(data);
    addTextConsole(data, false);
    data.clear();
}

void ViewPort::setHexView(bool b)
{
    bHexView = b;
}

void ViewPort::getMsg(QString s)
{
    qDebug() << s;
}
void ViewPort::finishedView()
{

}
void ViewPort::setSettingsPort()
{

}

#include "dlgrs.h"
#include "ui_dlgrs.h"

DlgRs::DlgRs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgRs)
{
    ui->setupUi(this);
    initDlgText();
    initSerilaPort();
    updateSetting(0);

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
    addTextConsole("Hello", true);
    addTextConsole("privet", false);

}

DlgRs::~DlgRs()
{
    delete ui;
}

void DlgRs::initDlgText()
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

void DlgRs::initChechBoxView(bool b)
{
    bEnabViewText = b;
}

void DlgRs::initSerilaPort()
{
    bOpenPort = false;
    serial = new QSerialPort();
    connect(serial,SIGNAL(error(QSerialPort::SerialPortError)),
            this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()),
            this, SLOT(readPort()));

}

DlgRs::Setting DlgRs::getSetting()
{
    return currentSetting;
}

void DlgRs::updateSetting(int n)
{
    bool b;
    if(bOpenPort)
    {
        openClosePort();
    }
        currentSetting.name = ui->comboPortRs->currentText();
        //baudrate
        currentSetting.baudRate = ui->comboBaudRate->currentText().toInt(&b, 0);
        currentSetting.strBaudRate = ui->comboBaudRate->currentText();
        // DataBits
        currentSetting.dataBits = static_cast<QSerialPort::DataBits>(
                    ui->comboDataBits->itemData(ui->comboDataBits->currentIndex()).toInt());
        currentSetting.strDataBits = ui->comboDataBits->currentText();
        //Parity
        currentSetting.parity = static_cast<QSerialPort::Parity>(
                        ui->comboParity->itemData(ui->comboParity->currentIndex()).toInt());
        currentSetting.strParity = ui->comboParity->currentText();
        //Stop bits
        currentSetting.stopBits = static_cast<QSerialPort::StopBits>(
                    ui->comboStopBits->itemData(ui->comboStopBits->currentIndex()).toInt());
        currentSetting.strStopBits = ui->comboStopBits->currentText();
        //Flow control
        currentSetting.flowControl = static_cast<QSerialPort::FlowControl>(
                    ui->comboFlowCtrl->itemData(ui->comboFlowCtrl->currentIndex()).toInt());
        currentSetting.strFlowControl = ui->comboFlowCtrl->currentText();
        //Additional options
        currentSetting.localEchoEnabled = false;


}

QStringList DlgRs::selectPort()
{
    QStringList list;
   foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
      list << info.portName();
   }
   return list;
}

void DlgRs::findPort()
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
    addTextConsole("Hello", true);
    addTextConsole("privet", false);
}

void DlgRs::openClosePort()
{

    if(bOpenPort)//port open -> close
    {

        if(serial->isOpen())
        {
            serial->close();
            ui->plainConsole->setEnabled(false);

        }
        ui->btOpenPort->setText("Open");
        bOpenPort = false;
    }
    else // port close -> open
    {

        Setting p = getSetting();

        if(!p.name.isEmpty())
        {



            serial->setPortName(p.name);

            if(serial->setBaudRate(p.baudRate)
                    && serial->setDataBits(p.dataBits)
                    && serial->setParity(p.parity)
                    && serial->setStopBits(p.stopBits)
                    && serial->setFlowControl(p.flowControl))
            {

                if(serial->open(QIODevice::ReadWrite))
                {

                    bOpenPort = true;
                    ui->plainConsole->setEnabled(true);
                    ui->btOpenPort->setText("Close");
                }
                else
                {

                }
            }
            else
            {

            }

        }
        else
        {

        }
    }
}

void DlgRs::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        QMessageBox::critical(this, tr("Critical Error"),
                              " serial = " + serial->errorString());
    }
}

void DlgRs::addTextConsole(QByteArray s, bool PrmWrt)
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

void DlgRs::readPort()
{
    QByteArray data = serial->readAll();
    addTextConsole(data, true);
    newData(data);
    data.clear();
}

void DlgRs::writeport(QByteArray b)
{
    QByteArray data = b;
    serial->write(data);
    addTextConsole(data, false);
    data.clear();
}

void DlgRs::setHexView(bool b)
{
    bHexView = b;
}

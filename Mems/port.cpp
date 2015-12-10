#include "port.h"

Port::Port(QObject *parent) : QObject(parent)
{
    qDebug() << "start port";
    connect(&serial, SIGNAL(error(QSerialPort::SerialPortError)),
            this, SLOT(handlerError(QSerialPort::SerialPortError)));
    connect(&serial, SIGNAL(readyRead()),
            this, SLOT(readPort()));

}

Port::~Port()
{
    qDebug() << "End port";
    emit finished_Port();
}

void Port::setSettingPort(Settings s)
{
    currentSetting.name = s.name;
    currentSetting.baudRate = s.baudRate;
    currentSetting.dataBits = (QSerialPort::DataBits)s.dataBits;
    currentSetting.parity = (QSerialPort::Parity) s.parity;
    currentSetting.stopBits = (QSerialPort::StopBits) s.stopBits;
    currentSetting.flowControl = (QSerialPort::FlowControl) s.flowControl;
}

void Port::connectPort()
{
    serial.setPortName(currentSetting.name);
    if(serial.open(QIODevice::ReadWrite))
    {
        if(serial.setBaudRate(currentSetting.baudRate)
                && serial.setDataBits(currentSetting.dataBits)
                && serial.setParity(currentSetting.parity)
                && serial.setStopBits(currentSetting.stopBits)
                && serial.setFlowControl(currentSetting.flowControl))
        {
            if(serial.isOpen())
            {
                emit error((currentSetting.name.toLocal8Bit() + " Открыт"));
            }
            else
            {
                serial.close();
                emit error(serial.errorString().toLocal8Bit());
            }
        }
    }
    else
    {
        emit error(serial.errorString().toLocal8Bit());
    }
}

void Port::handlerError(QSerialPort::SerialPortError errors)
{
    if((serial.isOpen())&& (errors == QSerialPort::ResourceError))
    {
        emit error(currentSetting.name.toLocal8Bit() + serial.errorString().toLocal8Bit());
        disconnectPort();
    }
}

void Port::disconnectPort()
{
    if(serial.isOpen())
    {
        serial.close();
        emit error(currentSetting.name.toLocal8Bit() + " Close");

    }
}

void Port::writeData(QByteArray bA)
{
    if(serial.isOpen())
    {
        serial.write(bA);
    }
}

void Port::readPort()
{
    QByteArray data;
    data.append(serial.readAll());
    emit outPort(data);
}







#ifndef SETTINGPORT_H
#define SETTINGPORT_H
#include <QObject>
#include <QString>
#include <QSerialPort>

namespace My {


class SettingPort
{

public:
     SettingPort();
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};
}

#endif // SETTINGPORT_H

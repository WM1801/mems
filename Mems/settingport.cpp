#include "settingport.h"

My::SettingPort::SettingPort()
{
    name = "noName";
    baudRate = 9600;
    dataBits = QSerialPort::Data8;
    parity = QSerialPort::NoParity;
    stopBits = QSerialPort::OneStop;
    flowControl = QSerialPort::NoFlowControl;
}


#ifndef PORT_H
#define PORT_H



#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <settingport.h>






class Port : public QObject
{
    Q_OBJECT
public:
    explicit Port(QObject *parent = 0);
    ~Port();
    struct Settings
    {
          QString name;
          qint32 baudRate;
          QSerialPort::DataBits dataBits;
          QSerialPort::Parity parity;
          QSerialPort::StopBits stopBits;
          QSerialPort::FlowControl flowControl;
    };

    QSerialPort serial;
    Settings currentSetting;

signals:
    void error(QString s);
    void finished_Port();
    void outPort(QByteArray bA);
public slots:
    void setSettingPort(My::SettingPort s);
    void connectPort();
    void disconnectPort();
    void writeData(QByteArray bA);
    void readPort();
    bool getIsOpenPort();
private slots:
    void handlerError(QSerialPort::SerialPortError errors);
};

 Q_DECLARE_METATYPE(Port::Settings)

#endif // PORT_H

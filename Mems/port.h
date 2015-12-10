#ifndef PORT_H
#define PORT_H



#include <QObject>
#include <QSerialPort>
#include <QDebug>


struct Settings
{
      QString name;
      qint32 baudRate;
      QSerialPort::DataBits dataBits;
      QSerialPort::Parity parity;
      QSerialPort::StopBits stopBits;
      QSerialPort::FlowControl flowControl;
};



class Port : public QObject
{
    Q_OBJECT
public:
    explicit Port(QObject *parent = 0);
    ~Port();
    QSerialPort serial;
    Settings currentSetting;

signals:
    void error(QString s);
    void finished_Port();
    void outPort(QByteArray bA);
public slots:
    void setSettingPort(Settings s);
    void connectPort();
    void disconnectPort();
    void writeData(QByteArray bA);
    void readPort();
private slots:
    void handlerError(QSerialPort::SerialPortError errors);
};

#endif // PORT_H

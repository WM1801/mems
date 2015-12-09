#ifndef DLGRS_H
#define DLGRS_H

#include <QDialog>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>
#include <QMessageBox>
#include <QDebug>
#include <QComboBox>
#include <console.h>
#include <QByteArray>

namespace Ui {
class DlgRs;
}

class DlgRs : public QDialog
{
    Q_OBJECT

public:
    explicit DlgRs(QWidget *parent = 0);
    ~DlgRs();

//************* serial port ***************
QSerialPort * serial;
//хранит состояние открыт порт или закрыт
bool bOpenPort;
//структура настроек порта
struct Setting {
    QString name;
    qint32 baudRate;
    QString  strBaudRate;
    QSerialPort::DataBits dataBits;
    QString strDataBits;
    QSerialPort::Parity parity;
    QString strParity;
    QSerialPort::StopBits stopBits;
    QString strStopBits;
    QSerialPort::FlowControl flowControl;
    QString strFlowControl;
    bool localEchoEnabled;
};
// текущие настройки
Setting currentSetting;
// возвращает текущие настройки из формы
Setting getSetting();

// инициализация порта
void initSerilaPort();
// список портов найденных в компьютере
QStringList selectPort();


//сигнал новые данные
signals:
void newData(QByteArray);

private slots:
// обновить настройки при изменении в интерфейсе
void updateSetting(int n);
//поиск портов
void findPort();
//открыть/ закрыть порт
void openClosePort();
// error port
void handleError(QSerialPort::SerialPortError error);
// чтение порта
void readPort();


public slots:
// запись в порт
void writeport(QByteArray b);


private:
// добавить текст в консоль
//PrmWrt - флаг отличия текста, принимаемого по РС и отправляемого
// в консоли отправке и приему соответствуют разные цвета
bool bEnabViewText; // разрешенгие на вывод в консоль
bool bHexView; //отображение данных в режиме hex
public slots:
void addTextConsole(QByteArray s, bool PrmWrt);
void setHexView(bool b);

//************** Форма ******************
private slots:
// инициализирует надписи
void initDlgText();
void initChechBoxView(bool b);



private:
    Ui::DlgRs *ui;
};

#endif // DLGRS_H

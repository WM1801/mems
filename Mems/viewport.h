#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QDialog>
#include <port.h>
#include <QDebug>
#include <QThread>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <settingport.h>

namespace Ui {
class ViewPort;
}

class ViewPort : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPort(QWidget *parent = 0);
    ~ViewPort();

private:
    Ui::ViewPort *ui;

    Port* port;
    QThread* thread;
    Port::Settings currentSetting;
    bool bOpenPort;
    bool bEnabViewText;
    bool bHexView;
 signals:
    void nSettingPort(My::SettingPort s);
    void sOpenPort();
    void sClosePort();
    void newData(QByteArray);
public slots:


    void initDlgText();
    void initSerilaPort();
    void setSettingsPort();
    void openClosePort();
    void writeData(QByteArray bA);
    void getMsg(QString s);
    void finishedView();
    void getData(QByteArray bA);
    void findPort();
    void updateSetting(int);
    QStringList selectPort();
    void setHexView(bool b);
    void initChechBoxView(bool b);
    Port::Settings getSetting();
    void addTextConsole(QByteArray s, bool PrmWrt);

};

#endif // VIEWPORT_H

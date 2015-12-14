#ifndef PARSDATA_H
#define PARSDATA_H

#include <QDialog>
#include <formatmsg.h>
#include <QByteArray>
#include <QDebug>
namespace Ui {
class ParsData;
}

class ParsData : public QDialog
{
    Q_OBJECT

public:
    explicit ParsData(QWidget *parent = 0);
    ~ParsData();
    QByteArray data;

signals:
    void newDataMems(FormatMsg::DataMems);
    void newDataMemsList(QList<FormatMsg::DataMems>);
public slots:

    void parsCom(QByteArray bA);
    void parsComList(QByteArray bA);
    FormatMsg::DataMems decode(QByteArray bA);

private:
    Ui::ParsData *ui;
};

#endif // PARSDATA_H

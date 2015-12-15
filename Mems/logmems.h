#ifndef LOGMEMS_H
#define LOGMEMS_H

#include <QDialog>

namespace Ui {
class LogMems;
}

class LogMems : public QDialog
{
    Q_OBJECT

public:
    explicit LogMems(QWidget *parent = 0);
    ~LogMems();
private:
    bool enabLog;

signals:
    void sPressEnabLog(bool, int);
    void sPressViewFile();
    void sGetNumbersRecords(int n);
public slots:
    void setProgressBarLog(int n);
private slots:
    void pressEnLog();
    void pressViewFile();
    int getNumbRecord();
private:
    Ui::LogMems *ui;
};

#endif // LOGMEMS_H

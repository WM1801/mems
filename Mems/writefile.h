#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <QObject>
#include <QDate>
#include <QTime>
#include <QFile>
#include <QProcess>

class WriteFile : public QObject
{
    Q_OBJECT
public:
    explicit WriteFile(QObject *parent = 0);

QString fileName;


signals:
    void newFile(QString);
public slots:
    QString createFile(QString name);
    void addStr(QString str);
    void addStr(QString name, QString str);
    void closeFile(QString nameFile);
    QString getNameFile();
    void viewFile(QString name);

};

#endif // WRITEFILE_H

#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <QObject>

class WriteFile : public QObject
{
    Q_OBJECT
public:
    explicit WriteFile(QObject *parent = 0);




signals:

public slots:
    void openFile(QString name);
    void addStr(QString str);
    void closeFile(QString name);

};

#endif // WRITEFILE_H

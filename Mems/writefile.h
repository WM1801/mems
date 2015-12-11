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
};

#endif // WRITEFILE_H

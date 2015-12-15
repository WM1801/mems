#include "writefile.h"

WriteFile::WriteFile(QObject *parent) : QObject(parent)
{

}

QString WriteFile::createFile(QString name)
{
    fileName.clear();
    fileName.append(name);
    QDate date;
    fileName.append(date.currentDate().toString("ddMMyy_"));
    QTime tm;
    fileName.append(tm.currentTime().toString("hhmmss"));
    fileName.append(".txt");
    QFile file;
    file.setFileName(fileName);
    if(file.exists()){}
    if(file.open(QIODevice::WriteOnly))
    {
        file.flush();
    }
    return fileName;

}

void WriteFile::addStr( QString str)
{
    QFile file;
    file.setFileName(fileName);
    if(file.exists())
    {
        if(file.open(QIODevice::Append))
        {
            str.append("\n");
            file.write(str.toLatin1());
            file.flush();
        }
    }
}

void WriteFile::addStr(QString name, QString str)
{
    QFile file;
    file.setFileName(name);
    if(file.exists())
    {

        if(file.open(QIODevice::Append))
        {
            str.append("\n");
            file.write(str.toLatin1());
            file.flush();
        }
    }
}


void WriteFile::closeFile(QString nameFile)
{
    QFile file;
    file.setFileName(nameFile);
    if(file.exists())
    {
        file.close();
    }

}

QString WriteFile::getNameFile()
{
    return fileName;
}

void WriteFile::viewFile(QString name)
{
    if(!name.isEmpty())
    {
        QProcess* proc = new QProcess(this);
        proc->start("explorer " + name);
    }
}


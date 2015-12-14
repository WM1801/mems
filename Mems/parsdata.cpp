#include "parsdata.h"
#include "ui_parsdata.h"

ParsData::ParsData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsData)
{
    ui->setupUi(this);
    data.clear();

}

ParsData::~ParsData()
{
    delete ui;
}


void ParsData::parsComList(QByteArray bA)
{
    QList<FormatMsg::DataMems> listMsg;
    FormatMsg::DataMems msg;
    data.append(bA);

    int pos = data.indexOf("$ST");
    if(pos < 0)
    {
        qDebug() << "not find $ST";
        data.clear();
    }
    else
    {
        if(pos>0)
        {
            QByteArray dan = data.mid(pos);
            data.clear();
            data.append(dan);
            pos = 0;
            dan.clear();
        }
        //
        while(data.size()>FormatMsg::SIZE)
        {
            msg = decode(data.mid(0, FormatMsg::SIZE));
            QByteArray dan = data.remove(0, FormatMsg::SIZE);
            data.clear();
            data.append(dan);
            dan.clear();
            listMsg.append(msg);

        }

        //
    }
    if(listMsg.size()>0)
    {
        emit newDataMemsList(listMsg);
    }
}

void ParsData::parsCom(QByteArray bA)
{
    FormatMsg::DataMems msg;
    data.append(bA);

    int pos = data.indexOf("$ST");
    if(pos < 0)
    {
        qDebug() << "not find $ST";
        //data.clear();
    }
    else
    {
        if(pos>0)
        {
            QByteArray dan = data.mid(pos);
            data.clear();
            data.append(dan);
            pos = 0;
            dan.clear();
        }
        //
        while(data.size()>FormatMsg::SIZE)
        {
            msg = decode(data.mid(0, FormatMsg::SIZE));
            QByteArray dan = data.remove(0, FormatMsg::SIZE);
            data.clear();
            data.append(dan);
            dan.clear();
            if(msg.enabDan)
            {
                emit newDataMems(msg);
            }
        }

        //
    }

    // temp
   // data.clear();

}

FormatMsg::DataMems ParsData::decode(QByteArray bA)
{
    //qDebug() << "start pars";
    FormatMsg::DataMems dan;
    dan.enabDan = FormatMsg::EN_FDAN;
   // qDebug() << "pars 1";
    qint16 mas[FormatMsg::SIZE];
   // qDebug() << "pars 2";
    if(bA.size()>=FormatMsg::SIZE-2)
    {
      //  qDebug() << "pars 3";
        qint16 f = 0xFF;
        for(int i = 0; i<FormatMsg::SIZE; i++ )
        {

            mas[i] = (qint16)(bA[i]&f);
        }
       // qDebug() << "pars 4";
        bA.clear();
        if((mas[FormatMsg::ADR_SYM0]==FormatMsg::SYM0)
                &(mas[FormatMsg::ADR_SYM1]==FormatMsg::SYM1)
                &(mas[FormatMsg::ADR_SYM2]==FormatMsg::SYM2))
        {
           // qDebug() << "pars 5";
            if(mas[FormatMsg::ADR_OVERUN]==FormatMsg::OVERUN_OK)
            {
           //     qDebug() << "pars 6";
                // dan OK
                qint16 byteH, byteL;
          /*Xa*/byteH = mas[FormatMsg::ADR_XAH];
                byteL = mas[FormatMsg::ADR_XAL];
                (byteH & 0x80)? dan.Xa = (-65536 + ((byteH<<8)|byteL)) : dan.Xa = ((byteH<<8)|byteL);
          /*Ya*/byteH = mas[FormatMsg::ADR_YAH];
                byteL = mas[FormatMsg::ADR_YAL];
                (byteH & 0x80)? dan.Ya = (-65536 + ((byteH<<8)|byteL)) : dan.Ya = ((byteH<<8)|byteL);
          /*Za*/byteH = mas[FormatMsg::ADR_ZAH];
                byteL = mas[FormatMsg::ADR_ZAL];
                (byteH & 0x80)? dan.Za = (-65536 + ((byteH<<8)|byteL)) : dan.Za = ((byteH<<8)|byteL);

          /*Xg*/byteH = mas[FormatMsg::ADR_XGH];
                byteL = mas[FormatMsg::ADR_XGL];
                (byteH & 0x80)? dan.Xg = (-65536 + ((byteH<<8)|byteL)) : dan.Xg = ((byteH<<8)|byteL);
          /*Yg*/byteH = mas[FormatMsg::ADR_YGH];
                byteL = mas[FormatMsg::ADR_YGL];
                (byteH & 0x80)? dan.Yg = (-65536 + ((byteH<<8)|byteL)) : dan.Yg = ((byteH<<8)|byteL);
          /*Zg*/byteH = mas[FormatMsg::ADR_ZGH];
                byteL = mas[FormatMsg::ADR_ZGL];
                (byteH & 0x80)? dan.Zg = (-65536 + ((byteH<<8)|byteL)) : dan.Zg = ((byteH<<8)|byteL);

          /*Xg*///byteH = mas[FormatMsg::ADR_XMH];
               // byteL = mas[FormatMsg::ADR_XML];
               // (byteH & 0x80)? dan.Xm = (-65536 + ((byteH<<8)|byteL)) : dan.Xm = ((byteH<<8)|byteL);
          /*Yg*///byteH = mas[FormatMsg::ADR_YMH];
                //byteL = mas[FormatMsg::ADR_YML];
                //(byteH & 0x80)? dan.Ym = (-65536 + ((byteH<<8)|byteL)) : dan.Ym = ((byteH<<8)|byteL);
          /*Zg*///byteH = mas[FormatMsg::ADR_ZMH];
                //byteL = mas[FormatMsg::ADR_ZML];
                //(byteH & 0x80)? dan.Zm = (-65536 + ((byteH<<8)|byteL)) : dan.Zm = ((byteH<<8)|byteL);

          /*Ta*/byteH = mas[FormatMsg::ADR_TAH];
                byteL = mas[FormatMsg::ADR_TAL];
                (byteH & 0x80)? dan.Ta = (-65536 + ((byteH<<8)|byteL)) : dan.Ta = ((byteH<<8)|byteL);
          /*Tg*/byteH = mas[FormatMsg::ADR_TGH];
                byteL = mas[FormatMsg::ADR_TGL];
                (byteL & 0x80)? dan.Tg = (-255 + ((byteH<<8)|byteL)) : dan.Tg = ((byteH<<8)|byteL);

                dan.count = mas[FormatMsg::ADR_COUNT];
                dan.numberMod = mas[FormatMsg::ADR_NUM_MODUL];
                dan.enabDan = FormatMsg::EN_TDAN;
             //    qDebug()<<"OK pars";
            }
            else
            {

                if(mas[FormatMsg::ADR_OVERUN]&FormatMsg::OVERUN_ACC)
                {
                    qDebug()<< "Overun Acc";
                }
                else
                {
                    if(mas[FormatMsg::ADR_OVERUN]&FormatMsg::OVERUN_GYRO)
                    {
                        qDebug()<< "Overun gyro";
                    }
                    else
                    {
                        if(mas[FormatMsg::ADR_OVERUN]&FormatMsg::OVERUN_MAGN)
                        {
                            qDebug()<< "Overun Magn";
                        }
                        else
                        {
                             qDebug()<< "Overun ? =" << mas[FormatMsg::ADR_OVERUN] ;
                        }
                    }
                }
            }

        }
        else
        {
            qDebug()<< "mas[012]!=$ST = " << mas[FormatMsg::ADR_SYM0]
                    <<  " =  " << mas[FormatMsg::ADR_SYM1]
                    <<  " =  " << mas[FormatMsg::ADR_SYM2];

        }
    }
    else
    {
        qDebug()<< "little size pars = " << bA.size();
    }
    bA.clear();
    return dan;
}



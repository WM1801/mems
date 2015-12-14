#ifndef FORMATMSG_H
#define FORMATMSG_H

#include <QObject>




class FormatMsg : public QObject
{
    Q_OBJECT
public:
    explicit FormatMsg(QObject *parent = 0);

signals:

public:
    struct DataMems
    {
    unsigned short sym0;
    unsigned short sym1;
    unsigned short sym2;
    unsigned short delta;
    unsigned short numberMod;
    unsigned short count;
    int Xa;
    int Ya;
    int Za;
    int Xg;
    int Yg;
    int Zg;
    int Xm;
    int Ym;
    int Zm;
    int Tg;
    int Ta;
    unsigned short Overun;
    unsigned short endSym1;
    unsigned short endSym2;
    bool enabDan;
    };

    DataMems currentData;



public slots:
    void append(FormatMsg::DataMems d);
    void clear();
public:

    //*************************************
    enum VALUE_BYTE
        {
            SYM0 = 0x24
            ,SYM1 = 0x53
            ,SYM2 = 0x54
            ,DELTA = 0x2C
            ,OVERUN_GYRO = 0x80
            ,OVERUN_ACC  = 0x04
            ,OVERUN_MAGN = 0x04
            ,OVERUN_OK = 0x47
            ,END_SYM1 = 0x5C
            ,END_SYM2 = 0x6E
            ,EN_FDAN = false
            ,EN_TDAN = true
        };
    Q_DECLARE_FLAGS( VALUE_BYTEs, VALUE_BYTE)
    //**************************************
    enum PROPERTY_COMMAND
        {
            SIZE = 35
            ,ADR_SYM0 = 0 //$
            ,ADR_SYM1 = 1 //S
            ,ADR_SYM2 = 2 //T
            ,ADR_NUM_MODUL = 4
            ,ADR_COUNT = 6
            ,ADR_XAH = 8
            ,ADR_XAL = 9
            ,ADR_YAH = 11
            ,ADR_YAL = 12
            ,ADR_ZAH = 14
            ,ADR_ZAL = 15
            ,ADR_XGH = 17
            ,ADR_XGL = 18
            ,ADR_YGH = 20
            ,ADR_YGL = 21
            ,ADR_ZGH = 23
            ,ADR_ZGL = 24
            ,ADR_TGH = 26
            ,ADR_TGL = 27
            ,ADR_TAH = 29
            ,ADR_TAL = 30
            ,ADR_OVERUN = 31
            ,ADR_END_SYM1 = 33
            ,ADR_END_SYM2 = 34
        };
    Q_DECLARE_FLAGS( PROPERTY_COMMANDs, PROPERTY_COMMAND)
};
    Q_DECLARE_OPERATORS_FOR_FLAGS(FormatMsg::PROPERTY_COMMANDs)
    Q_DECLARE_OPERATORS_FOR_FLAGS(FormatMsg::VALUE_BYTEs)



#endif // FORMATMSG_H

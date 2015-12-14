#include "formatmsg.h"



#define SIZE_MSG 34


FormatMsg::FormatMsg(QObject *parent) : QObject(parent)
{
    this->clear();
}

void FormatMsg::append(DataMems d)
{
    currentData.numberMod = d.numberMod;
    currentData.Xa = d.Xa;
    currentData.Ya = d.Ya;
    currentData.Za = d.Za;
    currentData.Xg = d.Xg;
    currentData.Yg = d.Yg;
    currentData.Zg = d.Zg;
    currentData.Xm = d.Xm;
    currentData.Ym = d.Ym;
    currentData.Zm = d.Zm;
    currentData.Tg = d.Tg;
    currentData.Ta = d.Ta;
    currentData.Overun = d.Overun;
    currentData.enabDan = d.enabDan;
}

void FormatMsg::clear()
{
    currentData.sym0 = SYM0;
    currentData.sym1 = SYM1;
    currentData.sym2 = SYM2;
    currentData.delta = DELTA;
    currentData.numberMod = 0;
    currentData.Xa = 0;
    currentData.Ya = 0;
    currentData.Za = 0;
    currentData.Xg = 0;
    currentData.Yg = 0;
    currentData.Zg = 0;
    currentData.Xm = 0;
    currentData.Ym = 0;
    currentData.Zm = 0;
    currentData.Tg = 0;
    currentData.Ta = 0;
    currentData.Overun = 0;
    currentData.endSym1 = END_SYM1;
    currentData.endSym2 = END_SYM2;
    currentData.enabDan = EN_FDAN;
}



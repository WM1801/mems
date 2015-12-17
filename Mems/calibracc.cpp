#include "calibracc.h"
#include "ui_calibracc.h"

#define SIZE_BUFFER 4000
#define Y_MAX_PLOT 20000
#define Y_MIN_PLOT -20000

CalibrAcc::CalibrAcc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrAcc)
{
    ui->setupUi(this);
    this->setWindowTitle("Calibration Accelerometer");

    ui->labValX ->setText("");
    ui->labValY ->setText("");
    ui->labValZ ->setText("");
    ui->labVal_X ->setText("");
    ui->labVal_Y ->setText("");
    ui->labVal_Z ->setText("");

    startStopCalibr = false;

    connect(ui->btStartCalbrAcc, SIGNAL(released()),
            this, SLOT(pressBtStartCalibrAcc()));

    rstStateClbr(&currentStateClbr);
    connect(ui->chbStateX, SIGNAL(clicked(bool)),
            this, SLOT(setViewChechBoxState()));
    connect(ui->chbState_X, SIGNAL(clicked(bool)),
            this, SLOT(setViewChechBoxState()));
    connect(ui->chbStateY, SIGNAL(clicked(bool)),
            this, SLOT(setViewChechBoxState()));
    connect(ui->chbState_Y, SIGNAL(clicked(bool)),
            this, SLOT(setViewChechBoxState()));
    connect(ui->chbStateZ, SIGNAL(clicked(bool)),
            this, SLOT(setViewChechBoxState()));
    connect(ui->chbState_Z, SIGNAL(clicked(bool)),
            this, SLOT(setViewChechBoxState()));
    setViewChechBoxState();

    listVector.clear();
    currentRecordData = 0;
    setProgressBar(currentRecordData);

    msgDlg = new MsgBox();
    msgDlg->setWindowTitle("Warning");
    connect(msgDlg, SIGNAL(start()),
            this,SLOT(pressedBtnWait()));
    curState = 0;

    initPlot();


}

CalibrAcc::~CalibrAcc()
{
    delete ui;
}


void CalibrAcc::getData(FormatMsg::DataMems d)
{
    currentRecordData++;
    if(currentRecordData<5)
    {
        updateCurrentState(getCurrentState(d));
    }


    if(currentRecordData>SIZE_BUFFER)
    {
        emit startReadData(false);
        //goto paste obrabotka
        //****
        // curState
        xPlot.clear();
        yPlot.clear();
        zPlot.clear();
        int i = 0;
        foreach (VectorGrav v, listVector) {
             xPlot.append(v.Ax);
             yPlot.append(v.Ay);
             zPlot.append(v.Az);
             axe.append(i++);
        }
        rePlot();




        //****
        if(getEndClbr())
        {
            pressBtStartCalibrAcc();
        }
        else
        {
            ui->btStartCalbrAcc->setText("Wait");
            newZikl();
            msgDlg->show();
        }
    }
    else
    {
        VectorGrav v;
        v.Ax = d.Xa;
        v.Ay = d.Ya;
        v.Az = d.Za;
        listVector.append(v);
    }
    setProgressBar(currentRecordData);
}

void CalibrAcc::newZikl()
{
    setViewChechBoxState();
    listVector.clear();
    currentRecordData = 0;
}

void CalibrAcc::pressBtStartCalibrAcc()
{
    qDebug() << "press but";
    startStopCalibr = !startStopCalibr;
    setViewChechBoxState();
    if(msgDlg->isVisible())
    {
        msgDlg->hide();
    }
    if(startStopCalibr)
    {
        newZikl();
        ui->btStartCalbrAcc->setText("Stop");
        emit startReadData(true);
    }
    else
    {
        qDebug() << "Size listData = " << listVector.size();
        ui->btStartCalbrAcc->setText("Start");
        emit startReadData(false);
    }

}

void CalibrAcc::rstStateClbr(StateClbr* s)
{
    s->TopX = false;
    s->Top_X = false;
    s->TopY = false;
    s->Top_Y = false;
    s->TopZ = false;
    s->Top_Z = false;
}

bool CalibrAcc::getEndClbr()
{
    bool b = false;
    if((currentStateClbr.TopX&currentStateClbr.Top_X)
        &((currentStateClbr.TopY&currentStateClbr.Top_Y)
          &(currentStateClbr.TopZ&currentStateClbr.Top_Z)))
    {
        b = true;
    }
    return b;
}

void CalibrAcc::setViewChechBoxState()
{
    if(currentStateClbr.TopX){ui->chbStateX->setChecked(true);}
    else {ui->chbStateX->setChecked(false);}
    if(currentStateClbr.Top_X){ui->chbState_X->setChecked(true);}
    else {ui->chbState_X->setChecked(false);}
    if(currentStateClbr.TopY){ui->chbStateY->setChecked(true);}
    else {ui->chbStateY->setChecked(false);}
    if(currentStateClbr.Top_Y){ui->chbState_Y->setChecked(true);}
    else {ui->chbState_Y->setChecked(false);}
    if(currentStateClbr.TopZ){ui->chbStateZ->setChecked(true);}
    else {ui->chbStateZ->setChecked(false);}
    if(currentStateClbr.Top_Z){ui->chbState_Z->setChecked(true);}
    else {ui->chbState_Z->setChecked(false);}
}

void CalibrAcc::setProgressBar(int n)
{
    int d = n*100/SIZE_BUFFER;
    ui->pBcurrentState->setValue(d);
}

CalibrAcc::StateClbr CalibrAcc::getCurrentState(FormatMsg::DataMems d)
{
    StateClbr s;
    rstStateClbr(&s);
    int state = 0;
    int x = qAbs(d.Xa);
    int y = qAbs(d.Ya);
    int z = qAbs(d.Za);
    if(x>y)
    {
        if(z>x)
        {
            if(d.Za>0) { state = 1; }
            else { state = 2;}
        }
        else
        {
            if(d.Xa>0) { state = 3; }
            else { state = 4; }
        }
    }
    else
    {
        if(z>y)
        {
            if(d.Za>0) { state = 1; }
            else { state = 2; }
        }
        else
        {
            if(d.Ya>0) { state = 5; }
            else { state = 6; }
        }

    }
    qDebug() << "State =" << state;
    switch(state)
    {
        case 1: {s.TopZ = true;  break;}
        case 2: {s.Top_Z = true; break;}
        case 3: {s.TopX = true; break;}
        case 4: {s.Top_X = true; break;}
        case 5: {s.TopY = true; break;}
        case 6: {s.Top_Y = true; break; }
        default:{}
    }
    curState = state;
    return s;
}

void CalibrAcc::pressedBtnWait()
{
    emit startReadData(true);
    ui->btStartCalbrAcc->setText("Stop");
    msgDlg->hide();
}

void CalibrAcc::updateCurrentState(StateClbr s)
{
    if(!currentStateClbr.TopX)
    {
        currentStateClbr.TopX = s.TopX;
    }
    if(!currentStateClbr.Top_X)
    {
        currentStateClbr.Top_X = s.Top_X;
    }
    if(!currentStateClbr.TopY)
    {
        currentStateClbr.TopY = s.TopY;
    }
    if(!currentStateClbr.Top_Y)
    {
        currentStateClbr.Top_Y = s.Top_Y;
    }
    if(!currentStateClbr.TopZ)
    {
        currentStateClbr.TopZ = s.TopZ;
    }
    if(!currentStateClbr.Top_Z)
    {
        currentStateClbr.Top_Z = s.Top_Z;
    }

}

void CalibrAcc::initPlot()
{
    xPlot.clear();
    yPlot.clear();
    zPlot.clear();
    axe.clear();

    connect(ui->widgPlot, SIGNAL(mouseRelease(QMouseEvent*)),
            this, SLOT(pressplot(QMouseEvent*)));
    ui->widgPlot->xAxis->setLabel("Count");
    ui->widgPlot->yAxis->setLabel("Value");
    ui->widgPlot->setInteraction(QCP::iRangeDrag, true);
    //ui->widgPlot->setFixedSize(this->size());
    ui->widgPlot->xAxis->setRange(0,SIZE_BUFFER);
    ui->widgPlot->yAxis->setRange(Y_MIN_PLOT,Y_MAX_PLOT);

    ui->widgPlot->addGraph();
    ui->widgPlot->graph(0)->setName("X");
    ui->widgPlot->graph(0)->setPen(QPen(Qt::red));

    ui->widgPlot->addGraph();
    ui->widgPlot->graph(1)->setName("Y");
    ui->widgPlot->graph(1)->setPen(QPen(Qt::green));

    ui->widgPlot->addGraph();
    ui->widgPlot->graph(2)->setName("Z");
    ui->widgPlot->graph(2)->setPen(QPen(Qt::blue));

}

void CalibrAcc::rePlot()
{
    ui->widgPlot->graph(0)->setData(axe, xPlot);
    ui->widgPlot->graph(1)->setData(axe, yPlot);
    ui->widgPlot->graph(2)->setData(axe, zPlot);
    ui->widgPlot->replot();
}

void CalibrAcc::pressplot(QMouseEvent *e)
{
    switch(e->button())
    {
        case (Qt::RightButton): {
                ui->widgPlot->legend->setVisible(!ui->widgPlot->legend->visible());
                ui->widgPlot->replot();
                break;
         }
        default:{}
    }
}

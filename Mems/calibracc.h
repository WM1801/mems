#ifndef CALIBRACC_H
#define CALIBRACC_H

#include <QDialog>
#include <formatmsg.h>
#include <QDebug>
#include <msgbox.h>



namespace Ui {
class CalibrAcc;
}

class CalibrAcc : public QDialog
{
    Q_OBJECT

    struct MatrixAcc
    {
        int ACC11;
        int ACC21;
        int ACC31;
        int ACC12;
        int ACC22;
        int ACC32;
        int ACC13;
        int ACC23;
        int ACC33;
        int ACC10;
        int ACC20;
        int ACC30;
    };

    struct VectorAcc
    {
        int Ax;
        int Ay;
        int Az;
        static const int One = 1;
    };

    struct VectorGrav
    {
        int Ax;
        int Ay;
        int Az;
    };

    struct StateClbr
    {
        bool TopX;
        bool Top_X;
        bool TopY;
        bool Top_Y;
        bool TopZ;
        bool Top_Z;
    };
    StateClbr currentStateClbr;
    int curState;
    bool startStopCalibr;

    QList<VectorGrav> listVector;
    int currentRecordData;

    MsgBox* msgDlg;

    QVector<double> xPlot;
    QVector<double> yPlot;
    QVector<double> zPlot;
    QVector<double> axe;

public:
    explicit CalibrAcc(QWidget *parent = 0);
    ~CalibrAcc();
private:
    Ui::CalibrAcc *ui;

signals:
    void startReadData(bool b);

public slots:
    void getData(FormatMsg::DataMems d);



private slots:
    void rstStateClbr(StateClbr *s);
    bool getEndClbr();
    void pressBtStartCalibrAcc();
    void setViewChechBoxState();
    void setProgressBar(int n);
    void pressedBtnWait();
    StateClbr getCurrentState(FormatMsg::DataMems d);
    void newZikl();
    void updateCurrentState(StateClbr s);
    void initPlot();
    void rePlot();
    void pressplot(QMouseEvent* e);



};

#endif // CALIBRACC_H

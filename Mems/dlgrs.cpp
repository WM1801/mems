#include "dlgrs.h"
#include "ui_dlgrs.h"

DlgRs::DlgRs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgRs)
{
    ui->setupUi(this);
}

DlgRs::~DlgRs()
{
    delete ui;
}

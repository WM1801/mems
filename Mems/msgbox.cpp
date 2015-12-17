#include "msgbox.h"
#include "ui_msgbox.h"

MsgBox::MsgBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgBox)
{
    ui->setupUi(this);
}

MsgBox::~MsgBox()
{
    delete ui;
}

void MsgBox::on_pushButton_clicked()
{
    emit start();
}

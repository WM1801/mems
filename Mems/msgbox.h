#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>

namespace Ui {
class MsgBox;
}

class MsgBox : public QDialog
{
    Q_OBJECT

public:
    explicit MsgBox(QWidget *parent = 0);
    ~MsgBox();

signals:
    void start();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MsgBox *ui;
};

#endif // MSGBOX_H

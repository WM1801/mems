#ifndef DLGRS_H
#define DLGRS_H

#include <QDialog>

namespace Ui {
class DlgRs;
}

class DlgRs : public QDialog
{
    Q_OBJECT

public:
    explicit DlgRs(QWidget *parent = 0);
    ~DlgRs();

private:
    Ui::DlgRs *ui;
};

#endif // DLGRS_H

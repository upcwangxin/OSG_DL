#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class myDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog(QWidget *parent = 0);
    ~myDialog();
    double speed=0;
    int index=0;
private slots:
    void on_pushButton_clicked();

    void on_determine_clicked();

    void on_cancel_clicked();

private:
    Ui::myDialog *ui;
signals:
    void sendDataStart(int,double);
    void sendDataEnd(double);
};

#endif // MYDIALOG_H

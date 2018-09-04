#ifndef MODELCONFIRM_H
#define MODELCONFIRM_H

#include <QDialog>

namespace Ui {

class ModelConfirm;
}

class ModelConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit ModelConfirm(QWidget *parent = 0);
    ~ModelConfirm();

private slots:
    void receiveModelScore(double);
    void on_pushButton_confirm_clicked();

private:
    Ui::ModelConfirm *ui;

};

#endif // MODELCONFIRM_H

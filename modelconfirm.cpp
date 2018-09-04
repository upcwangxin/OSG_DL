#include "modelconfirm.h"
#include "ui_modelconfirm.h"

ModelConfirm::ModelConfirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelConfirm)
{
    ui->setupUi(this);
}

ModelConfirm::~ModelConfirm()
{
    delete ui;
}


void ModelConfirm::on_pushButton_confirm_clicked()
{
    this->close();
}
void  ModelConfirm::receiveModelScore(double score)
{
   ui->label_CorrectRate->setText(QString::number(score*100)+"%");
}

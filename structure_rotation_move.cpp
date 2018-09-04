#include "structure_rotation_move.h"
#include "ui_structure_rotation_move.h"
#include <QTextStream>

structure_rotation_move::structure_rotation_move(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::structure_rotation_move)
{
    ui->setupUi(this);
}

structure_rotation_move::~structure_rotation_move()
{
    delete ui;
}
void structure_rotation_move::on_sure_clicked()
{
   int index=ui->comboBox->currentIndex();   //用于接受combox的index值
   moveValue=ui->distance->text().toDouble();
   emit sendMoveValue(moveValue,index);
}

void structure_rotation_move::on_cancle_clicked()
{
    this->close();
}

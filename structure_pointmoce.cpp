#include "structure_pointmoce.h"
#include "ui_structure_pointmoce.h"

structure_PointMoce::structure_PointMoce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::structure_PointMoce)
{
    ui->setupUi(this);
}

structure_PointMoce::~structure_PointMoce()
{
    delete ui;
}

void structure_PointMoce::on_move_clicked()
{
    double x=ui->coordinate_x->text().toDouble();
    double y=ui->coordinate_y->text().toDouble();
    double z=ui->coordinate_z->text().toDouble();
    sendPointMoveValue(x,y,z);
}

void structure_PointMoce::on_pushButton_2_clicked()
{
    this->close();
}

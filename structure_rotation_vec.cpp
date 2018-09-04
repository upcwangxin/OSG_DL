#include "structure_rotation_vec.h"
#include "ui_structure_rotation_vec.h"

structure_Rotation_Vec::structure_Rotation_Vec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::structure_Rotation_Vec)
{
    ui->setupUi(this);
    v.set(0,0,0);
}

structure_Rotation_Vec::~structure_Rotation_Vec()
{
    delete ui;
}

void structure_Rotation_Vec::on_Structure_Rotation_Vec_Start_clicked()
{
    float x=ui->Structure_Rotation_Vec_Vector_x->text().toFloat();
    float y=ui->Structure_Rotation_Vec_Vector_y->text().toFloat();
    float z=ui->Structure_Rotation_Vec_Vector_z->text().toFloat();
    this->v.set(x,y,z);
    this->speed=ui->Structure_Rotation_Vec_Speed->text().toDouble();
    emit sendDataVecStart(v,speed);
}

void structure_Rotation_Vec::on_Structure_Rotation_Vec_End_clicked()
{
    emit sendDataVecEnd(speed);
}

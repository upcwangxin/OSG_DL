#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    connect(this->parent(),SIGNAL(sendValueToSetting(double,double)),this,SLOT(receiveValueFromMain(double,double)));
    connect(this->parent(),SIGNAL(sendCoordinateToSetting(double,double,double,double,double,double)),this,SLOT(receiveCoordinateFromMain(double,double,double,double,double,double)));

}
Setting::~Setting()
{
    delete ui;
}
void Setting::on_Setting_Button_Apply_clicked()
{
    split_Speed=ui->split_Speed_lineEdit->text().toDouble();
    reconsitution_Speed=ui->reconsitution_Speed_lineEdit->text().toDouble();
    timeCycle=ui->lineEdit_PredictCycle->text().toInt(); 
    if(timeCycle!=0)
    {
       qDebug()<<timeCycle;
       emit sendTimeCycle(timeCycle);

    }
    if(checkValue(split_Speed,1) && checkValue(reconsitution_Speed,2))
    {
        sendSettingValue(split_Speed,reconsitution_Speed);
    }
    temp_reflush_speed=ui->temp_reflush_speed->text().toDouble();
    temp_coordinate_move_speed=ui->temp_coordinate_move_speed->text().toDouble();
    rotation_reflush_speed=ui->rotation_reflush_speed->text().toDouble();
    rotation_coordinate_move_speed=ui->rotation_coordinate_move_speed->text().toDouble();
    shake_reflush_speed=ui->shake_reflush_speed->text().toDouble();
    shake_coordinate_move_speed=ui->shake_coordinate_move_speed->text().toDouble();
    if(checkValue_Reflush_Speed(temp_reflush_speed,1) && checkValue_Reflush_Speed(rotation_reflush_speed,2) && checkValue_Reflush_Speed(shake_reflush_speed,3)
            && checkValue_Coordinate_Move_Speed(temp_coordinate_move_speed,1) && checkValue_Coordinate_Move_Speed(rotation_coordinate_move_speed,2) && checkValue_Coordinate_Move_Speed(shake_coordinate_move_speed,3))
    {
       sendSettingCoordinate(temp_reflush_speed,temp_coordinate_move_speed,rotation_reflush_speed,rotation_coordinate_move_speed,shake_reflush_speed,shake_coordinate_move_speed);
    }

}
bool Setting::checkValue(double value,int i)
{
   QString message="";
   if(value <= 50&&value >= 1)
   {
       return true;
   }
   message+=QString(i==1?QStringLiteral("拆分速度填写范围不正确"):QStringLiteral("重构速度填写范围不正确"));
   QMessageBox::critical(this,QStringLiteral("警告"),message,QMessageBox::Ok | QMessageBox::Default,0,0);
   return false;
}
bool Setting::checkValue_Reflush_Speed(double value, int i)
{
    QString message="";
    if(value <= 10&&value >= 1)
    {
        return true;
    }
    message+=QString(i==1?QStringLiteral("温度坐标值刷新速度不正确"):i==2?QStringLiteral("转速坐标值刷新速度不正确"):QStringLiteral("震动坐标值刷新速度不正确"));
    QMessageBox::critical(this,QStringLiteral("警告"),message,QMessageBox::Ok | QMessageBox::Default,0,0);
    return false;
}
bool Setting::checkValue_Coordinate_Move_Speed(double value, int i)
{
    QString message="";
    if(value <= 60&&value >= 1)
    {
        return true;
    }
    message+=QString(i==1?QStringLiteral("温度坐标移动速度不正确"):i==2?QStringLiteral("转速坐标移动速度不正确"):QStringLiteral("震动坐标移动速度不正确"));
    QMessageBox::critical(this,QStringLiteral("警告"),message,QMessageBox::Ok | QMessageBox::Default,0,0);
}
void Setting::on_Setting_Button_Cancle_clicked()
{
    this->close();
}
void Setting::receiveValueFromMain(double split_Speed, double reconsitution_Speed)
{
    ui->split_Speed_lineEdit->setText(QString::number(split_Speed));
    ui->reconsitution_Speed_lineEdit->setText(QString::number(reconsitution_Speed));
}
void Setting::receiveCoordinateFromMain(double temp_reflush_speed, double temp_coordinate_move_speed, double rotation_reflush_speed, double rotation_coordinate_move_speed, double shake_reflush_speed, double shake_coordinate_move_speed)
{
    ui->temp_reflush_speed->setText(QString::number(temp_reflush_speed));
    ui->temp_coordinate_move_speed->setText(QString::number(temp_coordinate_move_speed));
    ui->rotation_reflush_speed->setText(QString::number(rotation_reflush_speed));
    ui->rotation_coordinate_move_speed->setText(QString::number(rotation_coordinate_move_speed));
    ui->shake_reflush_speed->setText(QString::number(shake_reflush_speed));
    ui->shake_coordinate_move_speed->setText(QString::number(shake_coordinate_move_speed));
}


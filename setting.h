#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <String>
#include <iostream>
#include <thread>
#include <QDebug>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();

private slots:
    void on_Setting_Button_Apply_clicked();
    void on_Setting_Button_Cancle_clicked();

    bool checkValue(double value,int i);
    bool checkValue_Reflush_Speed(double value,int i);
    bool checkValue_Coordinate_Move_Speed(double value,int i);
    void receiveValueFromMain(double, double);
    void receiveCoordinateFromMain(double,double,double,double,double,double);

signals:
    void sendSettingValue(double,double);
    void sendSettingCoordinate(double,double,double,double,double,double);
    void sendTimeCycle(int);
private :
    QString message="";
    double split_Speed=0.0;
    double reconsitution_Speed=0.0;
    double temp_reflush_speed=0.0;
    double temp_coordinate_move_speed=0.0;
    double rotation_reflush_speed=0.0;
    double rotation_coordinate_move_speed=0.0;
    double shake_reflush_speed=0.0;
    double shake_coordinate_move_speed=0.0;
    int    timeCycle=10;
private:
    Ui::Setting *ui;
};

#endif // SETTING_H

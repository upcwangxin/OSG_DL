#ifndef STRUCTURE_ROTATION_VEC_H
#define STRUCTURE_ROTATION_VEC_H

#include <QDialog>

#include <osg/Vec3f>
namespace Ui {
class structure_Rotation_Vec;
}

class structure_Rotation_Vec : public QDialog
{
    Q_OBJECT
public:
    explicit structure_Rotation_Vec(QWidget *parent = 0);
    ~structure_Rotation_Vec();
    double speed=0;
    osg::Vec3f v;
private slots:
    void on_Structure_Rotation_Vec_Start_clicked();

    void on_Structure_Rotation_Vec_End_clicked();

private:
    Ui::structure_Rotation_Vec *ui;

signals:
    void sendDataVecStart(osg::Vec3f,double);
    void sendDataVecEnd(double);
};

#endif // STRUCTURE_ROTATION_VEC_H

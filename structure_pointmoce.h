#ifndef STRUCTURE_POINTMOCE_H
#define STRUCTURE_POINTMOCE_H

#include <QDialog>

namespace Ui {
class structure_PointMoce;
}

class structure_PointMoce : public QDialog
{
    Q_OBJECT

public:
    explicit structure_PointMoce(QWidget *parent = 0);
    ~structure_PointMoce();
signals:
    void sendPointMoveValue(double,double,double);
private slots:
    void on_move_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::structure_PointMoce *ui;
private:
    double coordinate_x;
    double coordinate_y;
    double coordinate_z;
};

#endif // STRUCTURE_POINTMOCE_H

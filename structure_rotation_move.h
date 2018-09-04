#ifndef STRUCTURE_ROTATION_MOVE_H
#define STRUCTURE_ROTATION_MOVE_H

#include <QDialog>

namespace Ui {
class structure_rotation_move;
}

class structure_rotation_move : public QDialog
{
    Q_OBJECT

public:
    explicit structure_rotation_move(QWidget *parent = 0);
    ~structure_rotation_move();
    double moveValue=0;
private slots:

    void on_sure_clicked();

    void on_cancle_clicked();

signals:
    void sendMoveValue(double,int);

private:
    Ui::structure_rotation_move *ui;
};

#endif // STRUCTURE_ROTATION_MOVE_H

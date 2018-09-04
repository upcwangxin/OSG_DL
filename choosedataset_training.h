#ifndef CHOOSEDATASET_TRAINING_H
#define CHOOSEDATASET_TRAINING_H

#include <QDialog>



namespace Ui {
class ChooseDataset_Training;
}

class ChooseDataset_Training : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDataset_Training(QWidget *parent = 0);
    ~ChooseDataset_Training();

private slots:
    void on_Open_Dataset_clicked();
    void on_Training_clicked();
    void sleep(unsigned int msec);
signals:
    void sendDataEnd(QString filepath);

private:
    Ui::ChooseDataset_Training *ui;

private:
    QString  file_name, file_path;
};

#endif // CHOOSEDATASET_TRAINING_H

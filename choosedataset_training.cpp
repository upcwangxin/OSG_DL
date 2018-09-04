#include "choosedataset_training.h"
#include "ui_choosedataset_training.h"
#include "QFileDialog"
#include "QFileInfo"
#include <QMessageBox>
#include <QTime>
#include <QProgressDialog>



ChooseDataset_Training::ChooseDataset_Training(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDataset_Training)
{
    ui->setupUi(this);
    ui->Training_progressBar->setRange(0,100000-1);
    ui->Training_progressBar->setValue(0);
}

ChooseDataset_Training::~ChooseDataset_Training()
{
    delete ui;
}

void ChooseDataset_Training::on_Open_Dataset_clicked()
{
    QString file_full=QFileDialog::getOpenFileName(this,tr("Open File"));
    QFileInfo fi;
    fi = QFileInfo(file_full);
    file_name = fi.fileName();
    file_path = file_full;
    ui->Dataset_Name->setText(file_name);
}

void ChooseDataset_Training::on_Training_clicked()
{
    for(int i=0;i<100000;i++)
       {
           for(int j=0;j<40000;j++);
           ui->Training_progressBar->setValue(i);
           if(i==100000-1)
           {
                   QMessageBox::StandardButton msgBox;
                   msgBox = QMessageBox::information(this,tr("训练完毕"),               //--这里是设置消息框标题
                          "训练完成,是否保存",                           //--这里是设置消息框显示的内容
                          QMessageBox::Ok |     //---这里是显示消息框上的按钮情况
                          QMessageBox::Cancel | QMessageBox::Escape );  //---这里与 键盘上的 escape 键结合。当用户按下该键，消息框将执行cancel按钮事件

                   if(msgBox == QMessageBox::Ok)
                   {
                       this->close();
                       QMessageBox::information(this, tr("提示"), "正在提取训练结果，请稍等", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                       emit sendDataEnd(file_path);        //向主页面传递数据集路径
                   }
            }
        }

}
void ChooseDataset_Training::sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,10);
    }
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QGridLayout>
#include <QTimer>
#include <QTime>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsql.h>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QInputDialog>
#include <QFileDialog>
#include <QApplication>
#include <qtextcodec.h>

#include <osgGA/StateSetManipulator>
#include <osgWidget/Widget>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ModularEmitter>
#include <osgParticle/RandomRateCounter>
#include <osgParticle/MultiSegmentPlacer>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/RadialShooter>
#include <osgParticle/PrecipitationEffect>
#include <osg/PositionAttitudeTransform>
#include <osg/Node>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osgText/Text>
#include <osgGA/GUIEventAdapter>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/LineWidth>
#include <osg/TexEnv>
#include <osg/TexGen>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Matrixd>
#include <osgDB/WriteFile>
#include <osg/Camera>
#include <osgFX/Scribe>

#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>

#include "rotatecallback.h"
#include "structure_rotation_quick.h"
#include "structure_rotation_vec.h"
#include "structure_rotation_move.h"
#include "structure_pointmoce.h"
#include "qcustomplot.h"
#include "setting.h"
#include "Python.h"
#include "choosedataset_training.h"
#include "modelconfirm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void receiveDataStart(int a,double b);
    void receiveDataEnd(double b);
    void receiveDataVecStart(osg::Vec3f v,double b);
    void receiveDataVecEnd(double b);
    void receiveMoveValue(double v,int index);
    void receivePointMove(double x,double y,double z);
    void receiveRangeChanged_Temp();
    void receiveRangeChanged_Rota();
    void receiveRangeChanged_Shake();
    void receiveSettingValue(double, double);
    void receiveSettingCoorinateValue(double,double,double,double,double,double);
    void receiveDatasetPath(QString);
    void receiveTimeCycle(int);
private slots:
    void openDataBase();
    void readDataBase();
    void buildTree(QStandardItem *item,int id,osg::ref_ptr<osg::Node> node);
    void on_dataTree_clicked(const QModelIndex &index);
    void searchNatureInDataBase(QString name);
    void sleep(unsigned int msec);
    void isNULL();
    void ChooseTraining();
    void databaseOperate(QString sql);
    void init();
    void initQCustomPlot();
    void initQCustomPlot_Temperature();
    void initQCustomPlot_Pressure();
    void initQCustomPlot_Speed();
    void initQCustomPlot_Other();
    void initQcustomPlot_HealthPredict();
    void ShowTrainingResult();
    void CycleTraining();
private slots:
    void on_action_File_OpenFile_triggered();
    void on_action_File_SaveFile_triggered();
    void on_action_File_OpenRecentFile_triggered();
    void on_action_File_Quit_triggered();
    void on_action_File_OpenFile_2_triggered();

    void on_action_Edit_SetColor_triggered(double r=-1,double g=-1,double b=-1,osg::ref_ptr<osg::Node> node=NULL);
    void on_action_Edit_Split_triggered();
    void on_action_Edit_Reconsitution_triggered();
    void on_action_Edit_Split_2_triggered();
    void on_action_Edit_Rotation_triggered();

    void on_action_Structure_Rotation_Vec_triggered();
    void on_action_Structure_Rotation_Quick_triggered();
    void on_action_Structure_Rotation_Quick_2_triggered();
    void on_action_Structure_quickMove_triggered();

    void on_action_quickMove_triggered();
    void on_action_pointMove_triggered();

    void on_action_View_ReOpen_triggered();
    void on_action_Setting_triggered();
    void on_action_ChooseTraining_triggered();
    void on_action_Choose_Dataset_triggered();

    void on_action_Predict_End_triggered();

    void on_action_predict_start_triggered();

    void on_action_modelConfirm_triggered();

signals:
    void sendValueToSetting(double,double);
    void sendCoordinateToSetting(double,double,double,double,double,double);
    void sendModelScore(double score);
private:
    Ui::MainWindow *ui;
    rotatecallback* r=NULL;
private:
    QStandardItemModel *model;
    QSqlDatabase data_base;
    QString sql="";
private:
    QMap<QString,QIcon> m_publicIconMap;
    QVector<QString> vector;
    QMap<QString,osg::ref_ptr<osg::Node>> nodeData;
private:
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Node> nodeSelect;
private:
    myDialog *myDialogUi;
    structure_Rotation_Vec *sRotation_Vec;
    structure_rotation_move *sMove_quick;
    structure_PointMoce *pointMove;
    Setting *setting;
    ChooseDataset_Training *chooseDataset;
    ModelConfirm *modelconfirm;
private:
    bool isScribe=false;
    double value=300;
    bool isSplit=false;
    int pyTime=0;
    int list_len;
    double *predict_list=new double[list_len];
    double model_score;
    bool isLoop=true;    //控制是否循环调用
    int indexPredict=1;
    int CycleT=10000;
    bool TC=true;
    QCPBars *rectBar ;
    QTimer temp_dataTimer;
    QTimer rotation_dataTimer;
    QTimer shake_dataTimer;
    QTimer pressure_dataTimer;
    QTimer timenow;
private :
    double split_Speed=0.0;
    double reconsitution_Speed=0.0;
    double temp_reflush_speed=0.0;
    double temp_coordinate_move_speed=0.0;
    double rotation_reflush_speed=0.0;
    double rotation_coordinate_move_speed=0.0;
    double shake_reflush_speed=0.0;
    double shake_coordinate_move_speed=0.0;
    double rate_predict=90;
};

#endif // MAINWINDOW_H

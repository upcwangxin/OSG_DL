#include "structure_rotation_quick.h"
#include "ui_mydialog.h"
#include <osg/PositionAttitudeTransform>
#include <osg/Node>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osgDB/ReadFile>
#include <osgText/Text>
#include <string>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/ViewerEventHandlers>
#include <osg/StateSet>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/LineWidth>
#include <iostream>
#include <osg/TexEnv>
#include <osg/TexGen>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Matrixd>
#include "rotatecallback.h"
#include <osgDB/WriteFile>
#include <osg/Camera>
#include <osgViewer/Viewer>
#include <iostream>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QTime>
myDialog::myDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myDialog)
{
    ui->setupUi(this);
}

myDialog::~myDialog()
{
    delete ui;
}

void myDialog::on_pushButton_clicked()
{

}

void myDialog::on_determine_clicked()
{
    index=ui->rotationAxis->currentIndex();
    speed=ui->rotationSpeed->text().toDouble();
    emit sendDataStart(index,speed);
}

void myDialog::on_cancel_clicked()
{
    emit sendDataEnd(speed);
}

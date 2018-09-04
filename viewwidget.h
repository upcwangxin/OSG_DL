#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QGridLayout>

#include <osgQt/GraphicsWindowQt>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Node>
#include <osgGA/TrackballManipulator>


class ViewWidget : public QWidget,public osgViewer::Viewer
{
    Q_OBJECT
public:
    explicit ViewWidget(QWidget *parent = 0);

    virtual void paintEvent(QPaintEvent *event);
    void ViewWidget::addNode(osg::ref_ptr<osg::Node> node);
private:
    osg::ref_ptr<osg::Group> root;

};

#endif // VIEWWIDGET_H

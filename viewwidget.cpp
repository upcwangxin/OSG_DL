#include "viewwidget.h"

ViewWidget::ViewWidget(QWidget *parent) : QWidget(parent)
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = 0;  //x偏移
    traits->y = 0;   //y偏移
    traits->width = 1000;
    traits->height = 800;
    traits->sharedContext = 0;
    traits->doubleBuffer = true;
    traits->windowDecoration = true;

    setThreadingModel(osgViewer::Viewer::SingleThreaded);
    osgQt::GraphicsWindowQt *gw = new osgQt::GraphicsWindowQt(traits);
    getCamera()->setGraphicsContext(gw);
    getCamera()->setProjectionMatrixAsPerspective(40.0,static_cast<double>(traits->width)/static_cast<double>(traits->height),0.1f,1000.0f);
    getCamera()->setViewport(new osg::Viewport(0,0,traits->width,traits->height));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(gw->getGLWidget(),0,0);
    setLayout(layout);
    osgGA::TrackballManipulator * tb = new osgGA::TrackballManipulator;
    tb->setHomePosition(osg::Vec3(0,100,20),osg::Vec3(0,0,0),osg::Z_AXIS);
    setCameraManipulator(tb);
}

void ViewWidget::paintEvent(QPaintEvent *event)
{
    frame();
    update();
}
void ViewWidget::addNode(osg::ref_ptr<osg::Node> node)
{
    root->addChild(node);
}


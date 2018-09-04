#ifndef ROTATECALLBACK_H
#define ROTATECALLBACK_H
#include <osg/Vec3f>
#include<osg/NodeCallback>

//回调函数，实现模型不停的旋转
class rotatecallback:public osg::NodeCallback
{
public:
    rotatecallback(double val,int i);
    rotatecallback();
    ~rotatecallback();
    void operator()(osg::Node* node,osg::NodeVisitor* nv);
    void set(double speed,int index,int choose);
    void set(osg::Vec3f v,double speed,int choose);
protected:
    double _rotateZ=0.0;
    double speed=1.0;
    int    index=0;
    int    choose=0;
    osg::Vec3f v;

};

#endif // ROTATECALLBACK_H

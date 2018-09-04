#include "rotatecallback.h"
#include<osg/PositionAttitudeTransform>
#include<osg/MatrixTransform>
#include<iostream>
#include<QTextStream>
//定义一个不断执行旋转动作的回调，它操作空间变换节点PositionAttitudeTransform不断改变旋转角度，实现动画效果。
rotatecallback::rotatecallback(double val,int i)
{
    speed=val;
    index=i;
}
rotatecallback::rotatecallback()
{

}

rotatecallback::~rotatecallback()
{

}
void rotatecallback::operator ()(osg::Node* node,osg::NodeVisitor* nv)
{
    osg::MatrixTransform* mat=dynamic_cast<osg::MatrixTransform*>(node);
    if(mat)
    {
        osg::Vec3f n;
        if(choose==1)
        {
            switch (index)
            {
                case 0:
                    n=osg::X_AXIS;
                    break;
                case 1:
                    n=osg::Y_AXIS;
                    break;
                case 2:
                    n=osg::Z_AXIS;
                    break;
                case 3:
                    n=osg::Vec3f(0,0,0);
                    break;
                default:
                    n=osg::Vec3f(0.0,0.0,0.0);
                    break;
            }
        }else if(choose==2){
            n.set(v.x(),v.y(),v.z());
        }
        osg::Quat quat(osg::DegreesToRadians(speed),n);//设置四元组  角度 旋转轴
        osg::Vec3d center=mat->getBound().center();
        osg::Matrixd m=mat->getMatrix();
        mat->setMatrix(m*osg::Matrixd::translate(-center)
                       *osg::Matrix::rotate(quat)
                       *osg::Matrixd::translate(center)
                       );
    }
    traverse(node,nv);
}
 void rotatecallback::set(double speed,int index,int choose)
{
   this->speed=speed;
   this->_rotateZ=0;
   this->index=index;
   this->choose=choose;
}
 void rotatecallback::set(osg::Vec3f v, double speed, int choose)
 {
     this->v=v;
     this->_rotateZ=0;
     this->speed=speed;
     this->choose=choose;
 }

#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "Python.h"
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
 /*     Py_Initialize();
       // 2种路径加载方式  一种绝对路径  一种EXE工程相对路径
       PyRun_SimpleString("import sys");
       PyRun_SimpleString("sys.path.append('G:/3dOSG/osg18.5.2')");  //加载文件绝对路径
//       PyRun_SimpleString("import sys");
//       QString setSysPath = QString("sys.path.append('%1')").arg(QCoreApplication::applicationDirPath());
//       PyRun_SimpleString(setSysPath.toStdString().c_str());

               if(!Py_IsInitialized())
               {
                         printf("PythonInit failed!\n");
               }
               PyObject*pModule = NULL;
               PyObject*pFunc = NULL;
//               PyObject*pResult = NULL;

//               int result=0;

//               PyObject* args = PyTuple_New(2);  // 2个参数
   //            PyObject* arg1 = PyLong_FromLong(4);    // 参数一设为4
   //            PyObject* arg2 = PyLong_FromLong(3);    // 参数二设为3
   //            PyTuple_SetItem(args, 0, arg1);
   //            PyTuple_SetItem(args, 1, arg2);
   //            args=Py_BuildValue("(i,i)",10,25);
               pModule= PyImport_ImportModule("trubine_create_dataset_svc");
               pFunc= PyObject_GetAttrString(pModule,"create_model");
               //pArg= Py_BuildValue("(s)","function with arguement");  //一个字符串参数
               PyEval_CallObject(pFunc,NULL);
   //            pFunc= PyObject_GetAttrString(pModule,"Add");          //两个整形的参数
   //            pArg= Py_BuildValue("(i,i)",10,25);
   //            pResult=PyEval_CallObject(pFunc,args);
   //           PyArg_Parse(pResult,"i",&result);
   //           qDebug()<<result;
       Py_Finalize();   */
    return a.exec();
}

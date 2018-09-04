#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    r=new rotatecallback();
    myDialogUi=new myDialog(this);
    sRotation_Vec=new structure_Rotation_Vec(this);
    sMove_quick=new structure_rotation_move(this);
    pointMove=new structure_PointMoce(this);
    setting=new Setting(this);
    chooseDataset=new ChooseDataset_Training(this);
    modelconfirm=new ModelConfirm(this);
    model=new QStandardItemModel(ui->dataTree);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("目录"));
    ui->dataTree->setModel(model);
    rectBar= new QCPBars(ui->widget_QcustomPlot_health->xAxis, ui->widget_QcustomPlot_health->yAxis);
    ui->dataTree->setEditTriggers(0);
    m_publicIconMap[QStringLiteral("treeItem_Project")]=QIcon(QStringLiteral(":/new/ico/Knob Remove.ico"));
    m_publicIconMap[QStringLiteral("treeItem_Leaf")]=QIcon(QStringLiteral(":/new/ico/Knob Blue.ico"));
    readDataBase();
    init();
    initQCustomPlot();// initialization customPlot
    //信号与槽函数建立联系
    connect(myDialogUi,SIGNAL(sendDataStart(int,double)),this,SLOT(receiveDataStart(int,double)));
    connect(myDialogUi,SIGNAL(sendDataEnd(double)),this,SLOT(receiveDataEnd(double)));
    connect(sRotation_Vec,SIGNAL(sendDataVecStart(osg::Vec3f,double)),this,SLOT(receiveDataVecStart(osg::Vec3f,double)));
    connect(sRotation_Vec,SIGNAL(sendDataVecEnd(double)),this,SLOT(receiveDataVecEnd(double)));
    connect(sMove_quick,SIGNAL(sendMoveValue(double,int)),this,SLOT(receiveMoveValue(double,int)));
    connect(pointMove,SIGNAL(sendPointMoveValue(double,double,double)),this,SLOT(receivePointMove(double,double,double)));
    connect(&temp_dataTimer,SIGNAL(timeout()),this,SLOT(receiveRangeChanged_Temp()));
    connect(&rotation_dataTimer,SIGNAL(timeout()),this,SLOT(receiveRangeChanged_Rota()));
    connect(&shake_dataTimer,SIGNAL(timeout()),this,SLOT(receiveRangeChanged_Shake()));
    connect(setting,SIGNAL(sendSettingValue(double,double)),this,SLOT(receiveSettingValue(double,double)));
    connect(setting,SIGNAL(sendSettingCoordinate(double,double,double,double,double,double)),this,SLOT(receiveSettingCoorinateValue(double,double,double,double,double,double)));
    connect(setting,SIGNAL(sendTimeCycle(int)),this,SLOT(receiveTimeCycle(int)));
    connect(chooseDataset,SIGNAL(sendDataEnd(QString)),this,SLOT(receiveDatasetPath(QString)));
    connect(this,SIGNAL(sendModelScore(double)),modelconfirm,SLOT(receiveModelScore(double)));   //父窗口向子窗口传递参数

    temp_dataTimer.start(1000);
    rotation_dataTimer.start(1000);
    shake_dataTimer.start(1000);
    ui->widget_QCustomPlot_temperature->legend->setVisible(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openDataBase()
{
    data_base=QSqlDatabase::addDatabase("QMYSQL");
    data_base.setHostName("127.0.0.1");
    data_base.setDatabaseName("osg");
    data_base.setUserName("root");
    data_base.setPassword("123456");
    if(!data_base.open())
    {
        qDebug()<<"failed to open mysql";
    }
}
void MainWindow::readDataBase()
{
    openDataBase();
    QStandardItem *itemChild;
    buildTree(itemChild,0,root);
    ui->widget->setSceneData(root);
}
void MainWindow::buildTree(QStandardItem *item,int id,osg::ref_ptr<osg::Node> node)
{    
    sql=QString("select * from t_modelInfo where iParent='%1'").arg(id);
    QSqlQuery query;
    bool success = query.exec(sql);
    if(!success){
        qDebug() << "查询osg失败";
    }
    query.seek(-1);
    if(id==0)
    {
        while(query.next())
        {
            QString  name= query.value(1).toString();
            QStandardItem *itemProject;
            if(query.value(5).toInt()==0)
            {
                itemProject=new QStandardItem(
                            m_publicIconMap[QStringLiteral("treeItem_Leaf")],name);

            }else{
                itemProject=new QStandardItem(
                            m_publicIconMap[QStringLiteral("treeItem_Project")],name);
            }
            root=new osg::Group;
            root->setName(query.value(1).toString().toStdString());
            buildTree(itemProject, query.value(0).toInt(),root);
            model->appendRow(itemProject);
        }
    }else
    {
        while(query.next())
        {
            QString  name= query.value(1).toString();
            QStandardItem *itemChild;
            osg::ref_ptr<osg::Node> n ;
            if(query.value(5).toInt()==0)
            {
                itemChild=new QStandardItem(
                            m_publicIconMap[QStringLiteral("treeItem_Leaf")],name);
                QString rootPath=query.value(7).toString();
                rootPath.replace("/","\\\\");
                osgDB::Options *a=new osgDB::Options(std::string("noTriStripPolygons"));
                n= osgDB::readNodeFile(rootPath.toStdString(),a);

                //n->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL,osg::StateAttribute::ON);//法线
                //n->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE);//模型光照关闭

                 n->setName(query.value(1).toString().toStdString());

               // const char *theName=query.value(1).toString().toLocal8Bit().data();
               // n->setName(theName);

                osg::ref_ptr<osg::MatrixTransform> mat=new osg::MatrixTransform;
                mat->setMatrix(osg::Matrix::translate(osg::Vec3(query.value(2).toFloat(),query.value(3).toFloat(),query.value(4).toFloat())));
                mat->addChild(n);
                //on_action_Edit_SetColor_triggered(query.value(11).toDouble(),query.value(12).toDouble(),query.value(13).toDouble(),n);
                nodeData[name]=n;
                vector.push_back(name);
                node->asGroup()->addChild(mat);
            }else{
                itemChild=new QStandardItem(
                            m_publicIconMap[QStringLiteral("treeItem_Project")],name);
                n=new osg::Node;
                node->asGroup()->addChild(n);
            }
            buildTree(itemChild, query.value(0).toInt(),node);
            item->appendRow(itemChild);
        }
    }
}
void MainWindow::on_dataTree_clicked(const QModelIndex &index)
{
    if(isScribe){
        osg::ref_ptr<osgFX::Scribe> scribe=dynamic_cast<osgFX::Scribe*>(nodeSelect->getParent(0));
        osg::ref_ptr<osg::Group> parentNode=scribe->getParent(0)->asGroup();
        parentNode->replaceChild(scribe.get(),nodeSelect.get());//replace
    }
    QString name=ui->dataTree->model()->itemData(index).values()[0].toString();
    searchNatureInDataBase(name);
    if(nodeData.contains(name)){
        nodeSelect=nodeData[name];
        osg::ref_ptr<osgFX::Scribe> scribeNode=new osgFX::Scribe();
        osg::ref_ptr<osg::Group> parentNode=nodeSelect->getParent(0)->asGroup();
        parentNode->replaceChild(nodeSelect.get(),scribeNode.get());
        scribeNode->addChild(nodeSelect.get());
        isScribe=true;
        ui->widget->setSceneData(root);
    }else{
        isScribe=false;
    }
}
void MainWindow::searchNatureInDataBase(QString name)
{
   ui->natureTableWidget->setRowCount(0);
   ui->natureTableWidget->clearContents();
   sql="select t_modelprop.cModelProp,t_modelprop.cModelPropVal from t_modelInfo,t_modelprop where t_modelprop.iModelID=t_modelinfo.iModelID and t_modelinfo.iModelName='"+name+"'";
   QSqlQuery query;
   bool success = query.exec(sql);
   if(!success){
       qDebug() << "查询osg失败";
   }
   query.seek(-1);
   ui->natureTableWidget->setColumnCount(2);
   QStringList header;
   header<<QString(QStringLiteral("属性"))<<QString(QStringLiteral("属性值"));
   int row=0;
   ui->natureTableWidget->verticalHeader()->setHidden(true);
   ui->natureTableWidget->setHorizontalHeaderLabels(header);
   ui->natureTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->natureTableWidget->insertRow(row);
   ui->natureTableWidget->setItem(0,0,new QTableWidgetItem(QStringLiteral("名字")));
   ui->natureTableWidget->item(0,0)->setTextAlignment(Qt::AlignCenter);
   ui->natureTableWidget->setItem(0,1,new QTableWidgetItem(name));
   ui->natureTableWidget->item(0,1)->setTextAlignment(Qt::AlignCenter);
   row=1;
   while(query.next())
   {
       ui->natureTableWidget->insertRow(row);
       ui->natureTableWidget->setItem(row,0,new QTableWidgetItem(query.value(0).toString()));
       ui->natureTableWidget->item(row,0)->setTextAlignment(Qt::AlignCenter);
       ui->natureTableWidget->setItem(row,1,new QTableWidgetItem(query.value(1).toString()));
       ui->natureTableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);
       row++;
   }
}
void MainWindow::on_action_File_OpenFile_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File"),"C:\\OSG\\data",tr("osgfile(*.osg)"));
    osgDB::Options *a=new osgDB::Options(std::string("noTriStripPolygons"));
    if(!fileName.isEmpty())
    {
        fileName.replace("/","\\\\");
        osg::ref_ptr<osg::Group> node = osgDB::readNodeFile(fileName.toStdString(),a)->asGroup();
        osg::ref_ptr<osg::MatrixTransform> mat=new osg::MatrixTransform;
        for(int i=0;i<node->getNumChildren();i++)
        {
             mat->addChild(node->getChild(i));
        }
        r->set(0,0,1);
        mat->setUpdateCallback(r);
        //root->replaceChild(root,mat);
        //root->addChild(mat.get());
        ui->widget->setSceneData(mat.get());

        QFile file("file.txt");
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
           std::cout<<"写入文件记录失败"<<std::endl;
        }else{

            QString text(fileName);
            QTextStream in(&file);
            in<<text;
            file.close();
        }
    }
}
void MainWindow::on_action_File_SaveFile_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),"C:\\OSG\\data",tr("osgfile(*.osg)"));
    if(!fileName.isEmpty())
    {
        osg::ref_ptr<osg::Group> root=ui->widget->getSceneData()->asGroup();
        osgDB::writeNodeFile(*root.get(),fileName.toStdString());
    }
}
void MainWindow::on_action_File_OpenRecentFile_triggered()
{
    osgDB::Options *a=new osgDB::Options(std::string("noTriStripPolygons"));
    QFile file("file.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::information(this,tr("错误"),tr("没有最近文件打开记录"));
    }
    else{
//        QTextStream in(&file);
//        osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(in.readAll().toStdString(),a);
//        osg::ref_ptr<osg::MatrixTransform> mat=new osg::MatrixTransform;

//        mat->addChild(node);
//        r->set(0,0,1);
//        mat->setUpdateCallback(r);
//        root->addChild(mat.get());

        file.close();
        //root->addChild(node.get());
        ui->widget->setSceneData(root);
    }
}
void MainWindow::on_action_File_Quit_triggered()
{
    this->close();
}
void MainWindow::on_action_Edit_SetColor_triggered(double r,double g,double b,osg::ref_ptr<osg::Node> node)
{
    //顶点着色器
    static const char* vertShader = {
        "varying vec2 MCposition;\n"
        "void main()\n"
        "{\n"
        "	MCposition = gl_Vertex.xy; \n"
        "	gl_Position = ftransform(); \n"
        "}\n"
    };
    //片元着色器
    static const char * fragShader = {
        "uniform vec3 BrickColor, MortarColor;\n"
        "uniform vec2 BrickSize;\n"
        "uniform vec2 BrickPct;\n"
        "varying vec2 MCposition;\n"
        "void main()\n"
        "{\n"
        "	vec3 color;\n"
        "	vec2 position, useBrick;\n"
        "   position = MCposition/BrickSize;\n"
        "	if (fract(position.y*0.5)>0.5)\n"
        "		position.x += 0.5;\n"
        "	position = fract(position);\n"
        "	useBrick = step(position, BrickPct);\n"
        "	color = mix(MortarColor, BrickColor, useBrick.x*useBrick.y);\n"
        "	gl_FragColor = vec4(color, 1.0);\n"
        "}\n"
    };
    if(nodeSelect!=NULL){
        osg::StateSet* stateset;
        if(r==-1&&g==-1&&b==-1&&node==NULL)
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            int i=qrand()%10;
            r=(double)i/10;
            int j=qrand()%10;
            g=(double)j/10;
            int k=qrand()%10;
            b=(double)k/10;
            stateset=nodeSelect->getOrCreateStateSet();
        }else{
            stateset=node->getOrCreateStateSet();
        }
        osg::ref_ptr<osg::Program> progrm=new osg::Program;
        osg::ref_ptr<osg::Uniform> MortarColor = new osg::Uniform("MortarColor", osg::Vec3(r, g, b));
        osg::ref_ptr<osg::Uniform> BrickSize = new osg::Uniform("BrickSize", osg::Vec2(1, 1));
        progrm->addShader(new osg::Shader(osg::Shader::VERTEX, vertShader));
        progrm->addShader(new osg::Shader(osg::Shader::FRAGMENT, fragShader));
        stateset->setAttributeAndModes(progrm, osg::StateAttribute::ON);

        stateset->addUniform(MortarColor);
        stateset->addUniform(BrickSize);
    }else{
       isNULL();
    }
}
void MainWindow::on_action_Edit_Split_triggered()
{
    isSplit=true;
    osg::ref_ptr<osg::MatrixTransform> mat;
    sql="select max(level) from t_modelInfo order by level desc";
    QSqlQuery query;
    bool success = query.exec(sql);
    if(!success){
        qDebug() << "查询osg失败";
    }
    query.seek(0);
    int maxLevel=query.value(0).toInt();
    for(int i=1;i<=maxLevel;i++)
    {
        sql=QString("select iModelName from t_modelInfo where level='%1'").arg(i);
        bool success = query.exec(sql);
        if(!success){
            qDebug() << "查询osg失败";
        }
        query.seek(0);
        osg::ref_ptr<osgFX::Scribe> scribe=dynamic_cast<osgFX::Scribe*>(nodeData[query.value(0).toString()]->getParent(0));
        if(scribe)
        {
            mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0)->getParent(0));
        }else{
            mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0));
        }
        for(int i=0;i<(value/split_Speed);i++){
            osg::Matrix m=mat->getMatrix();
            mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,0,split_Speed)));
            ui->widget->setSceneData(root);
            sleep(value);
        }
       if(i > 6)
       {
           sql=QString("select iModelName from t_modelInfo where level='%1'").arg(-i);
           success = query.exec(sql);
           if(!success){
               qDebug() << "查询osg失败";
           }
           query.seek(0);
           scribe=dynamic_cast<osgFX::Scribe*>(nodeData[query.value(0).toString()]->getParent(0));
           if(scribe)
           {
               mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0)->getParent(0));
           }else{
               mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0));
           }
           for(int i=0;i<(value/split_Speed);i++){
               osg::Matrix m=mat->getMatrix();
               mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,0,-split_Speed)));
               ui->widget->setSceneData(root);
               sleep(value);
           }
       }
    }
    ui->widget->setSceneData(root);
}
void MainWindow::on_action_Edit_Reconsitution_triggered()
{
   if(isSplit){
       osg::ref_ptr<osg::MatrixTransform> mat;
       sql="select max(level) from t_modelInfo order by level desc";
       QSqlQuery query;
       bool success = query.exec(sql);
       if(!success){
           qDebug() << "查询osg失败";
       }
       query.seek(0);
       int maxLevel=query.value(0).toInt();
       qDebug() << maxLevel;
       for(int i=maxLevel-1;i>=1;i--)
       {
           sql=QString("select iModelName from t_modelInfo where level='%1'").arg(i);
           bool success = query.exec(sql);
           if(!success){
               qDebug() << "查询osg失败";
           }
           query.seek(0);
           osg::ref_ptr<osgFX::Scribe> scribe=dynamic_cast<osgFX::Scribe*>(nodeData[query.value(0).toString()]->getParent(0));
           if(scribe)
           {
               mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0)->getParent(0));
           }else{
               mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0));
           }
           for(int i=0;i<(value/reconsitution_Speed);i++){
               osg::Matrix m=mat->getMatrix();
               mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,0,-reconsitution_Speed)));
               ui->widget->setSceneData(root);
               sleep(value);
           }

           sql=QString("select iModelName from t_modelInfo where level='%1'").arg(-i);
           success = query.exec(sql);
           if(!success){
               qDebug() << "查询osg失败";
           }
           query.seek(0);
           scribe=dynamic_cast<osgFX::Scribe*>(nodeData[query.value(0).toString()]->getParent(0));
           if(scribe)
           {
               mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0)->getParent(0));
           }else{
               mat=dynamic_cast<osg::MatrixTransform*>(nodeData[query.value(0).toString()]->getParent(0));
           }
           for(int i=0;i<(value/reconsitution_Speed);i++){
               osg::Matrix m=mat->getMatrix();
               mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,0,reconsitution_Speed)));
               ui->widget->setSceneData(root);
               sleep(value);
           }
       }
       ui->widget->setSceneData(root);
       isSplit=false;
   }
}
void MainWindow::on_action_Structure_Rotation_Vec_triggered()
{
   sRotation_Vec->show();
}
void MainWindow::on_action_Structure_Rotation_Quick_triggered()
{
    myDialogUi->show();
}
void MainWindow::receiveDataStart(int a, double b)
{
    if(nodeSelect!=NULL){
        r=new rotatecallback();
        r->set(0,0,1);
        osg::ref_ptr<osg::MatrixTransform> mat=dynamic_cast<osg::MatrixTransform*>(nodeSelect->getParent(0)->getParent(0));
        mat->setUpdateCallback(r);
        r->set(b,a,1);
    }else{
       isNULL();
    }
}
void MainWindow::receiveDataEnd(double b)
{
    if(nodeSelect!=NULL){
        osg::ref_ptr<osg::MatrixTransform> mat=dynamic_cast<osg::MatrixTransform*>(nodeSelect->getParent(0)->getParent(0));
        mat->removeUpdateCallback(r);
    }else{
       isNULL();
    }
}
void MainWindow::receiveDataVecStart(osg::Vec3f v, double b)
{
    if(nodeSelect!=NULL)
    {
        r=new rotatecallback();
        osg::ref_ptr<osg::MatrixTransform> mat=dynamic_cast<osg::MatrixTransform*>(nodeSelect->getParent(0)->getParent(0));
        mat->setUpdateCallback(r);
        r->set(v,b,2);
    }else{
       isNULL();
    }
}
void MainWindow::receiveDataVecEnd(double b)
{
    if(nodeSelect!=NULL){
        osg::ref_ptr<osg::MatrixTransform> mat=dynamic_cast<osg::MatrixTransform*>(nodeSelect->getParent(0)->getParent(0));
        mat->removeUpdateCallback(r);
    }else{
        isNULL();
    }
}
void MainWindow::receiveMoveValue(double v,int index)
{
    if(nodeSelect!=NULL){
        for(int i=0;i<value;i++){
            osg::ref_ptr<osg::MatrixTransform> mat=dynamic_cast<osg::MatrixTransform*>(nodeSelect->getParent(0)->getParent(0));
            //switch 语句判断平移方向
            osg::Matrix m=mat->getMatrix();
            switch(index){
            case 0 :
                mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,0,v/value)));
                break;
            case 1:
                 mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,0,-v/value)));
                 break;
            case 2:
                 mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(v/value,0,0)));
                 break;
            case 3:
                 mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(-v/value,0,0)));
                 break;
            case 4:
                 mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,v/value,0)));
                 break;
            case 5:
                 mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(0,-v/value,0)));
                 break;

            }
            ui->widget->setSceneData(root);
            sleep(100);
        }
    }else{
       isNULL();
    }
}
void MainWindow::receivePointMove(double x, double y, double z)
{
    if(nodeSelect!=NULL){
        double xValue=x-nodeSelect->getBound().center().x()*1.0;
        double yValue=y-nodeSelect->getBound().center().y()*1.0;
        double zValue=z-nodeSelect->getBound().center().z()*1.0;
        for(int i=0;i<value;i++){
            osg::ref_ptr<osg::MatrixTransform> mat=dynamic_cast<osg::MatrixTransform*>(nodeSelect->getParent(0)->getParent(0));
            osg::Matrix m=mat->getMatrix();
            mat->setMatrix(m*osg::Matrix::translate(osg::Vec3d(xValue/value,yValue/value,zValue/value)));
            ui->widget->setSceneData(root);
            sleep(100);
        }
    }else{
        isNULL();
    }
}
void MainWindow::receiveRangeChanged_Temp()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 5000);
    int valueKey = qrand()%9;
    ui->widget_QCustomPlot_temperature->graph(0)->addData(key,valueKey);
    ui->widget_QCustomPlot_temperature->graph(0)->removeDataBefore(key-temp_coordinate_move_speed);
    ui->widget_QCustomPlot_temperature->graph(0)->rescaleValueAxis(true);
    ui->widget_QCustomPlot_temperature->xAxis->setRange(key,temp_coordinate_move_speed,Qt::AlignRight);
    ui->widget_QCustomPlot_temperature->replot();
    temp_dataTimer.stop();
    temp_dataTimer.start(1000/temp_reflush_speed);
}
void MainWindow::receiveRangeChanged_Rota()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 5000);
    int valueKey = qrand()%10;
    ui->widget_QCustomPlot_Speed->graph(0)->addData(key,valueKey);
    ui->widget_QCustomPlot_Speed->graph(0)->removeDataBefore(key-rotation_coordinate_move_speed);
    ui->widget_QCustomPlot_Speed->graph(0)->rescaleValueAxis(true);
    ui->widget_QCustomPlot_Speed->xAxis->setRange(key,rotation_coordinate_move_speed,Qt::AlignRight);
    ui->widget_QCustomPlot_Speed->replot();
    rotation_dataTimer.stop();
    rotation_dataTimer.start(1000/rotation_reflush_speed);
}
void MainWindow::receiveRangeChanged_Shake()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 5000);
    int valueKey = qrand()%10;
    ui->widget_QCustomPlot_Last->graph(0)->addData(key,valueKey);
    ui->widget_QCustomPlot_Last->graph(0)->removeDataBefore(key-shake_coordinate_move_speed);
    ui->widget_QCustomPlot_Last->graph(0)->rescaleValueAxis(true);
    ui->widget_QCustomPlot_Last->xAxis->setRange(key,shake_coordinate_move_speed,Qt::AlignRight);
    ui->widget_QCustomPlot_Last->replot();
    shake_dataTimer.stop();
    shake_dataTimer.start(1000/shake_reflush_speed);
}
void MainWindow::receiveSettingValue(double split_Speed, double reconsitution_Speed)
{
    this->split_Speed=split_Speed;
    this->reconsitution_Speed=reconsitution_Speed;
    // write to database
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='拆分速度'").arg(split_Speed);
    databaseOperate(sql);
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='重构速度'").arg(reconsitution_Speed);
    databaseOperate(sql);
}
void MainWindow::receiveSettingCoorinateValue(double temp_reflush_speed, double temp_coordinate_move_speed, double rotation_reflush_speed, double rotation_coordinate_move_speed, double shake_reflush_speed, double shake_coordinate_move_speed)
{
    this->temp_reflush_speed=temp_reflush_speed;
    this->temp_coordinate_move_speed=temp_coordinate_move_speed;
    this->rotation_reflush_speed=rotation_reflush_speed;
    this->rotation_coordinate_move_speed=rotation_coordinate_move_speed;
    this->shake_reflush_speed=shake_reflush_speed;
    this->shake_coordinate_move_speed=shake_coordinate_move_speed;
    // write to database
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='温度坐标值刷新间隔'").arg(temp_reflush_speed);
    databaseOperate(sql);
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='温度坐标移动速度'").arg(temp_coordinate_move_speed);
    databaseOperate(sql);
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='转速坐标刷新间隔'").arg(rotation_reflush_speed);
    databaseOperate(sql);
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='转速坐标移动速度'").arg(rotation_coordinate_move_speed);
    databaseOperate(sql);
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='震动坐标刷新间隔'").arg(shake_reflush_speed);
    databaseOperate(sql);
    sql=QStringLiteral("update t_modelattribute set attributeValue='%1' where attributeName='震动坐标移动速度'").arg(shake_coordinate_move_speed);
    databaseOperate(sql);
}
void MainWindow::receiveDatasetPath(QString datasetPath)
{
      std::string str = datasetPath.toStdString();
      const char* ch = str.c_str();                 //路径转化为字符串数组，传递参数的关键
      qDebug()<<ch;
      Py_Initialize();
      // 2种路径加载方式  一种绝对路径  一种EXE工程相对路径
      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.path.append('G:/3dOSG/osg18.6.8final')");  //加载文件绝对路径

      if(!Py_IsInitialized())
      {
                printf("PythonInit failed!\n");
      }
      PyObject*pModule = NULL;
      PyObject*pFunc = NULL;
      PyObject* args = PyTuple_New(1);
      PyObject*arg1 = NULL;
      PyObject*resultlist = NULL;
      arg1=Py_BuildValue("s",ch);
      PyTuple_SetItem(args, 0, arg1);
      pModule= PyImport_ImportModule("NewSVC");
      pFunc= PyObject_GetAttrString(pModule,"predict_model");       //调用py文件的函数接口  不能加括号
      resultlist=PyEval_CallObject(pFunc,args);

      double it;
      list_len=PyObject_Size(resultlist);      //列表长度
      PyObject *list_item = NULL;            //python类型的列表元素
      double   *double_item=new double[list_len];  //c类型的列表元素

      for(int i = 0; i < list_len; i++)
      {
      list_item = PyList_GetItem(resultlist, i); //根据下标取出python列表中的元素
      it=PyFloat_AsDouble(list_item);   //转换为c++类型的数据  PyArg_Parse用于格式字符串
      if(i==0) model_score=it;          //模型得分存储在列表第一个值
      else     double_item[i]=it;
      }
      for(int i = 0; i < list_len; i++)
      predict_list[i]=double_item[i];
      qDebug()<<model_score;
      Py_Finalize();
      ShowTrainingResult();
}

void MainWindow::receiveTimeCycle(int c)
{
     TC=false;
     CycleT=c*1000;
     qDebug()<<CycleT;
     ShowTrainingResult();
}
void MainWindow::on_action_quickMove_triggered()
{
    sMove_quick->show();
}
void MainWindow::on_action_pointMove_triggered()
{
    pointMove->show();
}
void MainWindow::on_action_File_OpenFile_2_triggered()
{
    on_action_File_OpenFile_triggered();
}
void MainWindow::on_action_Structure_Rotation_Quick_2_triggered()
{
    myDialogUi->show();
}
void MainWindow::on_action_Structure_quickMove_triggered()
{
    sMove_quick->show();
}
void MainWindow::on_action_Choose_Dataset_triggered()
{
   chooseDataset->show();
}
void MainWindow::on_action_Edit_Split_2_triggered()
{
    on_action_Edit_Split_triggered();
}
void MainWindow::on_action_Edit_Rotation_triggered()
{
    on_action_Edit_Reconsitution_triggered();
}
void MainWindow::on_action_View_ReOpen_triggered()
{
    root=NULL;
    ui->widget->setSceneData(root);
    nodeSelect=NULL;
    readDataBase();
}
void MainWindow::on_action_Setting_triggered()
{
   sendValueToSetting(split_Speed, reconsitution_Speed);
   sendCoordinateToSetting(temp_reflush_speed,temp_coordinate_move_speed
                           ,rotation_reflush_speed,rotation_coordinate_move_speed
                           ,shake_reflush_speed,shake_coordinate_move_speed);
   setting->show();
}
void MainWindow::init()
{
    sql=QStringLiteral("select attributeValue from t_modelattribute where attributeName='拆分速度' or attributeName='重构速度' or attributeName='温度坐标值刷新间隔' or attributeName='温度坐标移动速度' or attributeName='转速坐标刷新间隔' or attributeName='转速坐标移动速度' or attributeName='震动坐标刷新间隔' or attributeName='震动坐标移动速度'");
    qDebug()<<sql;
    QSqlQuery query;
    bool success = query.exec(sql);
    if(!success){
        qDebug() << "查询osg失败";
    }
    query.first();
    split_Speed=query.value(0).toDouble();
    query.next();
    reconsitution_Speed=query.value(0).toDouble();
    query.next();
    temp_reflush_speed=query.value(0).toDouble();
    query.next();
    temp_coordinate_move_speed=query.value(0).toDouble();
    query.next();
    rotation_reflush_speed=query.value(0).toDouble();
    query.next();
    rotation_coordinate_move_speed=query.value(0).toDouble();
    query.next();
    shake_reflush_speed=query.value(0).toDouble();
    query.next();
    shake_coordinate_move_speed=query.value(0).toDouble();
}
void MainWindow::initQCustomPlot()
{
   initQCustomPlot_Temperature();
   initQCustomPlot_Pressure();
   initQCustomPlot_Speed();
   initQCustomPlot_Other();
}
void MainWindow::initQCustomPlot_Temperature()
{
    ui->widget_QCustomPlot_temperature->addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    ui->widget_QCustomPlot_temperature->graph(0)->setPen(pen);
    ui->widget_QCustomPlot_temperature->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->widget_QCustomPlot_temperature->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->widget_QCustomPlot_temperature->xAxis->setAutoTickStep(false);
    ui->widget_QCustomPlot_temperature->xAxis->setTickStep(4);
    ui->widget_QCustomPlot_temperature->axisRect()->setupFullAxesBox();
    ui->widget_QCustomPlot_temperature->yAxis->setLabel(QStringLiteral("温度/℃"));
    ui->widget_QCustomPlot_temperature->xAxis->setLabel(QStringLiteral("时间/t"));
}
void MainWindow::initQCustomPlot_Pressure()
{
    ui->widget_QCustomPlot_Pressure->addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    ui->widget_QCustomPlot_Pressure->graph(0)->setPen(pen);
    ui->widget_QCustomPlot_Pressure->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->widget_QCustomPlot_Pressure->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->widget_QCustomPlot_Pressure->xAxis->setAutoTickStep(false);
    ui->widget_QCustomPlot_Pressure->xAxis->setTickStep(4);
    ui->widget_QCustomPlot_Pressure->axisRect()->setupFullAxesBox();
    ui->widget_QCustomPlot_Pressure->yAxis->setLabel(QStringLiteral("压力/KP"));
    ui->widget_QCustomPlot_Pressure->xAxis->setLabel(QStringLiteral("时间/t"));
}
void MainWindow::initQCustomPlot_Speed()
{
    ui->widget_QCustomPlot_Speed->addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    ui->widget_QCustomPlot_Speed->graph(0)->setPen(pen);
    ui->widget_QCustomPlot_Speed->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->widget_QCustomPlot_Speed->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->widget_QCustomPlot_Speed->xAxis->setAutoTickStep(false);
    ui->widget_QCustomPlot_Speed->xAxis->setTickStep(4);
    ui->widget_QCustomPlot_Speed->axisRect()->setupFullAxesBox();
    ui->widget_QCustomPlot_Speed->yAxis->setLabel(QStringLiteral("速度/m/s"));
    ui->widget_QCustomPlot_Speed->xAxis->setLabel(QStringLiteral("时间/t"));
}
void MainWindow::initQCustomPlot_Other()
{
    ui->widget_QCustomPlot_Last->addGraph();
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    ui->widget_QCustomPlot_Last->graph(0)->setPen(pen);
    ui->widget_QCustomPlot_Last->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->widget_QCustomPlot_Last->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->widget_QCustomPlot_Last->xAxis->setAutoTickStep(false);
    ui->widget_QCustomPlot_Last->xAxis->setTickStep(4);
    ui->widget_QCustomPlot_Last->axisRect()->setupFullAxesBox();
    ui->widget_QCustomPlot_Last->yAxis->setLabel(QStringLiteral("震动/mm/s"));
    ui->widget_QCustomPlot_Last->xAxis->setLabel(QStringLiteral("时间/t"));
}
void MainWindow::initQcustomPlot_HealthPredict()
{
    //int plottableCount = ui->widget_QcustomPlot_health->plottableCount();
    //clearPlottables()
    ui->widget_QcustomPlot_health->clearGraphs();
    ui->widget_QcustomPlot_health->removeGraph(1);
    //清除上次图像数据
    rectBar->clearData();
    ui->widget_QcustomPlot_health->xAxis->setTicks(false);    //setTicks控制是否自动生成坐标
    ui->widget_QcustomPlot_health->xAxis->setLabel(QStringLiteral("健康监测系统"));
    ui->widget_QcustomPlot_health->yAxis->setLabel(QStringLiteral("单位/%"));
    ui->widget_QcustomPlot_health->legend->setVisible(true);
    //ui->widget_QcustomPlot_health->xAxis->setRange(0, 4);
    ui->widget_QcustomPlot_health->yAxis->setRange(70, 100);
   /* ui->widget_QcustomPlot_health->xAxis->setTickStep(1);
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(255, 255, 255));
    gradient.setColorAt(0, QColor(70, 70, 70));
    ui->widget_QcustomPlot_health->setBackground(QBrush(gradient));*/
    QVector<double> xBar,yBar;
    xBar <<1;
    yBar<<rate_predict;
    rectBar->setAntialiased(false);
    rectBar->setPen(QPen(QColor(255, 168,255 ).lighter(130)));
    rectBar->setBrush(QColor(0, 168, 140));

    rectBar->setData(xBar, yBar);
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString   current_date =current_date_time.toString("ddd hh:mm:ss");
    ui->label_time->setText(current_date);
    ui->widget_QcustomPlot_health->replot();
}

void MainWindow::sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,10);
    }
}
void MainWindow::isNULL()
{
   QMessageBox::about(NULL,QStringLiteral("提示"),QStringLiteral("请点选模型"));
}
void MainWindow::databaseOperate(QString sql)
{
    QSqlQuery query;
    query.exec(sql);
}


void MainWindow::on_action_ChooseTraining_triggered()
{
    Py_Initialize();                       //按钮触发函数开始载入Python初始化语句  放入循环语句程序只能一次执行
    ChooseTraining();
    Py_Finalize();
}

void MainWindow::ChooseTraining()
{
   while(pyTime<5)             //全局变量pyTime 控制循环
   {
    pyTime=pyTime+1;
    qDebug()<<"You use it for"<<pyTime<<"times";
      // 2种路径加载方式  一种绝对路径  一种EXE工程相对路径
      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.path.append('G:/3dOSG/osg18.6.8final')");  //加载文件绝对路径
//    PyRun_SimpleString("import sys");
//    QString setSysPath = QString("sys.path.append('%1')").arg(QCoreApplication::applicationDirPath());
//    PyRun_SimpleString(setSysPath.toStdString().c_str());
      if(!Py_IsInitialized())
      {
                printf("PythonInit failed!\n");
      }
      PyObject*pModule = NULL;
      PyObject*pFunc = NULL;
      PyObject*pResult = NULL;

      float result=0;
      pModule= PyImport_ImportModule("SVC");
      pFunc= PyObject_GetAttrString(pModule,"get_result");       //调用py文件的函数接口  不能加括号
      pResult=PyEval_CallObject(pFunc,NULL);
      PyArg_Parse(pResult,"f",&result);
      qDebug()<<result;
      ui->correctRate->setText(QString::number(result*100)+"%");
      rate_predict=100*result;
      initQcustomPlot_HealthPredict();                           //调用柱状图函数
      sleep(10000);                                             //延时函数 延时10S QTime未能成功
   }
}
void MainWindow::ShowTrainingResult()
{
      //使用Timer定时器不堵塞主进程  若在初始化时定义信号槽 始终报内存分配错误
     // 师兄不才 有待师弟师妹解决此问题  师弟师妹加油,师兄看好你们呦
    if(TC)
    {
        connect(&timenow, SIGNAL(timeout()), this, SLOT(CycleTraining()));
        timenow.start(CycleT);
    }
    else
    {
        timenow.stop();
        timenow.start(CycleT);
    }
}
void MainWindow::CycleTraining()
{
        ui->label_status->setText(QStringLiteral("正在监测"));
        for(;indexPredict < list_len;)
        {
               if(isLoop)
               {
                   ui->correctRate->setText(QString::number(predict_list[indexPredict]*100)+"%");
                   if(predict_list[indexPredict]*100 < 93)
                   {
                       ui->label_ErrorName->setText(QStringLiteral("当前可能发生故障的部件"));
                       QString str = vector.front();
                       vector.remove(0);
                       vector.push_back(str);
                       ui->modelName01->setText(str);
                       ui->modelCorrect01->setText(QString::number((1-predict_list[indexPredict])*100)+"%");
                       if(predict_list[indexPredict]*100 < 92)
                       {
                           str = vector.front();
                           vector.remove(0);
                           vector.push_back(str);
                           ui->modelName02->setText(str);
                           ui->modelCorrect02->setText(QString::number((1-predict_list[indexPredict])*100 - 1)+"%");
                       }
                   }else{
                       ui->label_ErrorName->setText("");
                       ui->modelName01->setText("");
                       ui->modelCorrect01->setText("");
                       ui->modelName02->setText("");
                       ui->modelCorrect02->setText("");
                   }
                   rate_predict=100*predict_list[indexPredict];
                   initQcustomPlot_HealthPredict();
                   indexPredict=indexPredict+1;
                   break;                //定时器调用一次就退出
               }
               else
               {
                 ui->label_status->setText(QStringLiteral("暂停监测"));
                 break;
               }
        }
}

void MainWindow::on_action_Predict_End_triggered()
{
      isLoop=false;     //结束监测
}

void MainWindow::on_action_predict_start_triggered()
{
      isLoop=true;     //开始监测
      ShowTrainingResult();
}

void MainWindow::on_action_modelConfirm_triggered()
{
     emit sendModelScore(model_score);
     qDebug()<<model_score;
     modelconfirm->show();
}

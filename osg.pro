#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T18:46:00
#
#-------------------------------------------------

QT       += core gui
QT+=sql
QT += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET = osg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    viewwidget.cpp \
    rotatecallback.cpp \
    structure_rotation_move.cpp \
    structure_rotation_vec.cpp \
    structure_rotation_quick.cpp \
    structure_pointmoce.cpp \
    qcustomplot.cpp \
    setting.cpp \
    choosedataset_training.cpp \
    modelconfirm.cpp

HEADERS  += mainwindow.h \
    viewwidget.h \
    rotatecallback.h \
    structure_rotation_move.h \
    structure_rotation_vec.h \
    structure_rotation_quick.h \
    structure_pointmoce.h \
    qcustomplot.h \
    setting.h \
    myt.h \
    choosedataset_training.h \
    modelconfirm.h

FORMS    += mainwindow.ui \
    mydialog.ui \
    structure_rotation_move.ui \
    structure_rotation_vec.ui \
    structure_pointmoce.ui \
    setting.ui \
    choosedataset_training.ui \
    modelconfirm.ui
CONFIG+=debug_and_release
INCLUDEPATH +=E:\OSG\include
CONFIG(debug, debug|release) {
    LIBS+=-LE:\OSG\lib -lOpenThreadsd -losgd -losgDBd -losgUtild -losgGAd -losgViewerd -losgTextd  -losgQtd -losgParticled -losgFXd
} else {
    LIBS+=-LE:\OSG\lib -lOpenThreads -losg -losgDB -losgUtil -losgGA -losgViewer -losgText  -losgQt -losgParticle
}

RESOURCES += \
    tubiao.qrc

INCLUDEPATH +=D:/learn/python32/include/
LIBS += D:/learn/python32/libs/python36.lib

DISTFILES += \
    MyModel.py \
    MyF.py \
    SVC.py \
    NewSVC.py \
    data_analysis.py


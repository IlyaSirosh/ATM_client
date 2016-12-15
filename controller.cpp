#include "controller.h"
#include <QHBoxLayout>

Controller::Controller(QWidget *parent) :
    QWidget(parent),
    _power(new QPushButton()),
    _close(new QPushButton()),
    _eject(new QPushButton()),
    _working(false)
{
    _power->setText("Turn ON");
    _close->setText("Close");
    _eject->setText("Eject");

    connect(_power,SIGNAL(clicked()),this,SLOT(power()));
    connect(_close,SIGNAL(clicked()),this,SIGNAL(close()));
    connect(_eject,SIGNAL(clicked()),this,SIGNAL(eject()));
    createLayout();
}


Controller::~Controller(){
    delete _power;
    delete _close;
    delete _eject;
}

 void Controller::createLayout(){
    QHBoxLayout* layout= new QHBoxLayout(this);

    layout->addWidget(_power);
    layout->addWidget(_eject);
    layout->addWidget(_close);

    _power->setFixedWidth(90);
    _eject->setFixedWidth(70);
    _close->setFixedWidth(70);
 }

 void Controller::power(){

     if(_working){
         _power->setText("Turn ON");
         _working = false;
     }else{
         _power->setText("Turn OFF");
         _working = true;
     }

     emit on_power(_working);
 }

 void Controller::stopWorking(){
     _power->setText("Turn ON");
     _working = false;
 }

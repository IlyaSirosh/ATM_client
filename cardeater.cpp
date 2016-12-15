#include "cardeater.h"
#include <QVBoxLayout>

CardEater::CardEater(QWidget *parent) :
    QWidget(parent),
    _input(new QLineEdit()),
    _submit(new QPushButton()),
    _card("")
{
    _submit->setText("Вставити картку");

    connect(_submit,SIGNAL(clicked()),this,SLOT(submit()));

    createLayout();
}

CardEater::~CardEater(){

    delete _input;
    delete _submit;

}

void CardEater::createLayout(){

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(_input);
    layout->addWidget(_submit);
}

void CardEater::submit(){

    _card = _input->text();

    emit getCard(_card);
}

const QString& CardEater::getCardNumber() const{
    return _card;
}

bool CardEater::isInjected()const{
    return _card.length()!=0;
}

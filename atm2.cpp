#include "atm2.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QDateTime>
#include <QDebug>

ATM2::ATM2(QWidget *parent) :
    QWidget(parent),
    _mainScreen(new QTextBrowser()),
    _checkScreen(new QTextBrowser()),
    _keypad(new KeyPad()),
    _cardEater(new CardEater()),
    _controller(new Controller()),
    _info(new QLabel()),
    _client(new Client()),
    _teller(new CashTeller())
{
    connect(_keypad, SIGNAL(digitClicked(int)),this,SLOT(keypadClicked(int)));
    connect(_keypad, SIGNAL(okClicked()),this,SLOT(keypadOK()));
    connect(_keypad, SIGNAL(removeClicked()),this,SLOT(keypadRemove()));


    connect(_controller,SIGNAL(on_power(bool)),this,SLOT(contrPower(bool)));
    connect(_controller,SIGNAL(close()),this,SLOT(contrClose()));
    connect(_controller,SIGNAL(eject()),this,SLOT(contrEject()));

    connect(_cardEater,SIGNAL(getCard(QString)),this,SLOT(cardInjected(QString)));


    connect(this, SIGNAL(close_app()),
                    QApplication::instance(), SLOT(quit()));
    _cardEater->setVisible(false);
    createLayout();


}

ATM2::~ATM2()
{
    delete _mainScreen;
    delete _checkScreen;
    delete _keypad;
    delete _cardEater;
    delete _controller;
    delete _info;
    delete _client;
}

void ATM2::createLayout(){

    QGridLayout* main = new QGridLayout(this);
    QVBoxLayout* left = new QVBoxLayout;
    QVBoxLayout* right = new QVBoxLayout;

    left->addWidget(_mainScreen);
    left->addWidget(_info);
    left->addWidget(_keypad);

    right->addWidget(_cardEater);
    right->addWidget(_checkScreen);
    right->addWidget(_controller);

    left->setAlignment(_keypad,Qt::AlignHCenter);
    _keypad->setFixedSize(200,150);

    right->setAlignment(_checkScreen,Qt::AlignHCenter);
    _checkScreen->setFixedSize(150,200);

    right->setAlignment(_controller,Qt::AlignHCenter);
    _controller->setFixedWidth(240);

    main->addLayout(left,0,0);
    main->addLayout(right,0,1);

}

void ATM2::keypadClicked(int digit){

    if(_state==ATMState::CHOOSE_STATE){
        if(digit==5){
            close();
        }else{

            doOperation(digit+2);
        }
    }else
    if(_state==ATMState::GET_PIN_STATE){
            _result+=digit;
            _mainScreen->append("*");
    }else
    if(_state==ATMState::GET_CASH){

        if(digit==1){
            _client->request("04:50");
            checkForGetCash("50");
        }else
        if(digit==2){
            _client->request("04:200");
            checkForGetCash("200");
        }else
        if(digit==3){
            _client->request("04:500");
            checkForGetCash("500");
        }else
        if(digit==4){
            _client->request("04:1000");
            checkForGetCash("1000");
        }if(digit==5){
            close();
        }


    }else
    if(_state==ATMState::WANT_TO_CONTINUE){

        if(digit==1){
            checkPassword();
        }else{
            ejectCard();
        }
     }

}

void ATM2::doOperation(int digit){


    if(digit==3){
        _client->request("04");
        QString resp = _client->response();

        _checkScreen->setText("Ваш баланс:"+resp);
        wantToContinue();
    }else
    if(digit==4){
        showCashMenu();
    }


}

void ATM2::keypadOK(){

    if(_state==ATMState::GET_PIN_STATE){
        _client->request("02:"+_result);
        _result = "";
        QString resp = _client->response();

        if(resp=="1"){
            _state.startChoose();
            showMenu();
        }else{
            _mainScreen->setText("Невірний пароль!");
            ejectCard();
        }
    }
}

void ATM2::keypadRemove(){
    if(_result.length()>0){
        _result = _result.left(_result.length()-1);
        QString main = _mainScreen->toPlainText();
        _mainScreen->setText(main.leftJustified(main.length()-1));
    }

}

void ATM2::contrPower(bool on){
    if(on){
        _state.startWorking();
        _client->connect("localhost",1111);
        injectCard();
    }else{
        if(_cardEater->isInjected()){
            ejectCard();
        }else{
            _state.stopWorking();
        }
        close();
        _cardEater->setVisible(false);
    }
}

void ATM2::contrClose(){
    _state.stopWorking();
    close();
    emit close_app();
}

void ATM2::contrEject(){
    ejectCard();
}

void ATM2::ejectCard(){
    if(_state.working()){
        _info->setText("Заберіть картку");
        _state.stopWorking();
    }
}

void ATM2::cardInjected(const QString& card){
    _client->request("01:"+card);

    qDebug()<<(card);

    QString resp = _client->response();

    if(resp=="1"){
        checkPassword();
    }else{
        _mainScreen->setText("Помилка. Цієї картки немає в базі даних");
        ejectCard();
    }
}

void ATM2::showMenu(){
    _mainScreen->setText("1 - Переглянути баланс\n2 - Зняти готівку\n3 - Завершити роботу");
    _info->setText("Зробіть ваш вибір");
    _state.startChoose();
}

void ATM2::showCashMenu(){
    _mainScreen->setText("1 - 50грн\n2 - 200 грн\n3 - 500грн\n4 - 1000грн\n5 - Завершити роботу");
    _info->setText("Зробіть ваш вибір");
    _state.startGetCash();
}

void ATM2::wantToContinue(){
    _mainScreen->setText("Ви хочете продовжити роботу?\n1 - Так\n2 - Ні");
    _info->setText("Зробіть ваш вибір");
    _state.startWantToContinue();
    _checkScreen->setText("");
}

void ATM2::checkPassword(){
    _info->setText("Введіть PIN");
    _state.startGetPin();
}

void ATM2::injectCard(){
    _info->setText("Вставте картку");
    _cardEater->setVisible(true);
}

void ATM2::close(){
    _client->request("05");
    ejectCard();
    _client->disconnect();
}
void ATM2::printCheck(const QString& cash){
    QDateTime date;
    QString d = date.toString();
    _checkScreen->setText("VAV Bank, Kyiv\n"+d+"\n"+"get "+cash+" UAN");
}

void ATM2::checkForGetCash(const QString& cash){

    QString resp = _client->response();

    if(resp=="1"){
        _teller->withdrawCash(cash);
        printCheck(cash);
    }else{
        _checkScreen->setText("Cannot get cash");
    }

    wantToContinue();
}

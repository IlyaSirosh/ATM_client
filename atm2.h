#ifndef ATM2_H
#define ATM2_H

#include <QWidget>
#include <QTextBrowser>
#include <QLabel>
#include "keypad.h"
#include "cardeater.h"
#include "controller.h"
#include "atmstate.h"
#include "client.h"
#include "cashteller.h"

class ATM2 : public QWidget
{
    Q_OBJECT

public:
    explicit ATM2(QWidget *parent = 0);
    ~ATM2();

signals:
    void close_app();

public slots:

    void keypadClicked(int);
    void keypadOK();
    void keypadRemove();

    void contrPower(bool);
    void contrClose();
    void contrEject();

    void cardInjected(const QString&);

private:
    QTextBrowser* _mainScreen;
    QTextBrowser* _checkScreen;
    KeyPad* _keypad;
    CardEater* _cardEater;
    Controller* _controller;
    ATMState _state;
    QLabel* _info;
    QString _result;
    Client* _client;
    CashTeller* _teller;

    void createLayout();
    void doOperation(int);
    void ejectCard();
    void showMenu();
    void showCashMenu();
    void wantToContinue();
    void checkPassword();
    void injectCard();
    void close();
    void printCheck(const QString&);
    void checkForGetCash(const QString&);
};

#endif // ATM2_H

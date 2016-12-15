#ifndef ATMSTATE_H
#define ATMSTATE_H
#include <QObject>

class ATMState : public QObject
{
    Q_OBJECT
public:
    explicit ATMState(QObject *parent = 0);
    ATMState(bool,bool,bool,bool,bool);

    static ATMState CHOOSE_STATE;
    static ATMState GET_PIN_STATE;
    static ATMState WORK_STATE;
    static ATMState GET_CASH;
    static ATMState WANT_TO_CONTINUE;

    bool operator == (const ATMState&)const;

    void stopWorking();
    void startWorking();
    bool working()const;

    void startChoose();
    void startGetPin();
    void startGetCash();
    void startWantToContinue();

signals:

public slots:

private:
    bool _working;
    bool _choosingOperation;
    bool _gettingPIN;
    bool _gettingCash;
    bool _wantToContinue;
};

#endif // ATMSTATE_H

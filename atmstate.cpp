#include "atmstate.h"

ATMState ATMState::CHOOSE_STATE(true,true,false,false,false);
ATMState ATMState::GET_PIN_STATE(true,false,true,false,false);
ATMState ATMState::WORK_STATE(true,false,false,false,false);
ATMState ATMState::GET_CASH(true,false,false,true,false);
ATMState ATMState::WANT_TO_CONTINUE(true,false,false,false,true);

ATMState::ATMState(QObject *parent) :
    QObject(parent),
    _working(false),
    _choosingOperation(false),
    _gettingPIN(false),
    _gettingCash(false),
    _wantToContinue(false)
{

}

ATMState::ATMState(bool w,bool ch,bool p,bool c,bool cn):
    QObject(0),
    _working(w),
    _choosingOperation(ch),
    _gettingPIN(p),
    _gettingCash(c),
    _wantToContinue(cn)
{

}

 bool ATMState::operator == (const ATMState& b)const{
     return _working == b._working&&
     _choosingOperation == b._choosingOperation&&
     _gettingPIN == b._gettingPIN&&
             _gettingCash == b._gettingCash&&
             _wantToContinue == b._wantToContinue;
 }

 void ATMState::stopWorking(){
     _wantToContinue = _gettingCash=_choosingOperation =_gettingPIN = _working = false;
 }

 void ATMState::startWorking(){
    _working = true;
 }


 void ATMState::startChoose(){
     _choosingOperation = true;
     _gettingPIN = false;
     _gettingCash = false;
     _wantToContinue = false;
 }

 void ATMState::startGetPin(){
     _gettingPIN = true;
     _choosingOperation = false;
     _gettingCash = false;
     _wantToContinue = false;
 }

 void ATMState::startGetCash(){
     _gettingPIN = false;
     _choosingOperation = false;
     _gettingCash = true;
     _wantToContinue = false;
 }

 void ATMState::startWantToContinue(){
     _gettingPIN = false;
     _choosingOperation = false;
     _gettingCash = false;
     _wantToContinue = true;
 }

 bool ATMState::working()const{
     return _working;
 }

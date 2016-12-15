#include <QApplication>
#include "client.h"
#include "atm2.h"
#include "keypad.h"
#include "cardeater.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ATM2 form;

    form.show();


    return a.exec();
}

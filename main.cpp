#include <QCoreApplication>
#include "client.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client client;

    client.connect("localhost",1234);

    if(client.isConnected()){

    }else{

    }

    client.disconnect();

    return a.exec();
}

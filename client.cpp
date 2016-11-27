#include "client.h"

Client::Client(QObject *parent) : QObject(parent), _socket(0)
{

}

void Client::connect(const QString &host, int port){

    _socket = new QTcpSocket(this);

    _socket->connectToHost(host, port);

    if(_socket->waitForConnected(5000))
    {
        qDebug() << "Connected!";
    }
    else
    {
        qDebug() << "Not connected!";
    }

}


bool Client::isConnected()const{
    return _socket!=0;
}

void Client::disconnect(){
    qDebug() << "disconnected";
    _socket->close();
    _socket = 0;
}

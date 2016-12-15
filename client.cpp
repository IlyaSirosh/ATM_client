#include "client.h"

Client::Client(QObject *parent) : QObject(parent), _socket(0),_connected(false)
{

}

void Client::connect(const QString &host, int port){

    _socket = new QTcpSocket(this);

    _socket->connectToHost(host, port);

    if(_socket->waitForConnected(5000))
    {
        qDebug() << "Connected!";
        _connected = true;
    }
    else
    {
        qDebug() << "Not connected!";
    }

}


bool Client::isConnected()const{
    return _connected;
}

void Client::disconnect(){
    qDebug() << "disconnected";
    _socket->close();
    _socket = 0;
    _connected = false;
}

void Client::request(const QString& req){

    if(_connected){
        QByteArray data;
        data.append(req);
        _socket->write(data);
    }
}

QString Client::response(){

    QByteArray data;

    if(_socket->waitForReadyRead(5000))
        data = _socket->readAll();

    return QString(data);
}

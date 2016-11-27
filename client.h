#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void connect(const QString& host, int port);
    bool isConnected()const;
    void disconnect();
signals:

public slots:

private:
    QTcpSocket *_socket;
};

#endif // CLIENT_H

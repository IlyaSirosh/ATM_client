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
    QString response();
    void request(const QString& req);
signals:

public slots:

private:
    QTcpSocket *_socket;
    bool _connected;
};

#endif // CLIENT_H

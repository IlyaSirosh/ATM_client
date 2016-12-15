#ifndef CASHTELLER_H
#define CASHTELLER_H

#include <QObject>

class CashTeller : public QObject
{
    Q_OBJECT
public:
    explicit CashTeller(QObject *parent = 0);

    void withdrawCash(const QString&){}

signals:

public slots:
};

#endif // CASHTELLER_H

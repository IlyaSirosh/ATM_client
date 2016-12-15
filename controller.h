#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QPushButton>

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(QWidget *parent = 0);
    ~Controller();

    void stopWorking();
signals:
    void on_power(bool);
    void close();
    void eject();
public slots:
    void power();
private:
    QPushButton* _power;
    QPushButton* _close;
    QPushButton* _eject;
    bool _working;

    void createLayout();
};

#endif // CONTROLLER_H

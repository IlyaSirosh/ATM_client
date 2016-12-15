#ifndef KEYPAD_H
#define KEYPAD_H
#include <QPushButton>

class KeyPad : public QWidget
{
    Q_OBJECT
public:
    explicit KeyPad(QWidget *parent = 0);

signals:
    void digitClicked(int digit);
    void okClicked();
    void removeClicked();
public slots:

private:
    QPushButton *buttons[12];

    void createLayout();
};

#endif // KEYPAD_H

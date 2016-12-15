#include "keypad.h"
#include <QSignalMapper>
#include <QGridLayout>
KeyPad::KeyPad(QWidget *parent) : QWidget(parent)
{
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SIGNAL(digitClicked(int)));

    for (int i = 0; i < 10; ++i) {
        QString text = QString::number(i);
        buttons[i] = new QPushButton(text, this);
        signalMapper->setMapping(buttons[i], i);
        connect(buttons[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
    }
    buttons[10] = new QPushButton("OK", this);
    buttons[11] = new QPushButton("<-", this);

    connect(buttons[10], SIGNAL(clicked()), this, SIGNAL(okClicked()));
    connect(buttons[11], SIGNAL(clicked()), this, SIGNAL(removeClicked()));

    createLayout();
}

void KeyPad::createLayout()
{
     QGridLayout *layout = new QGridLayout(this);
     layout->setMargin(6);
     layout->setSpacing(6);

     for (int i = 0; i < 9; ++i)
        layout->addWidget(buttons[i + 1], i / 3, i % 3);
     layout->addWidget(buttons[0], 3, 1);
     layout->addWidget(buttons[10], 3, 0);
     layout->addWidget(buttons[11], 3, 2);
 }

#ifndef CARDEATER_H
#define CARDEATER_H
#include <QLineEdit>
#include <QPushButton>


class CardEater : public QWidget
{
    Q_OBJECT
public:
    explicit CardEater(QWidget *parent = 0);
    ~CardEater();
    const QString& getCardNumber() const;
    bool isInjected()const;
signals:

public slots:
    void submit();
private:
    QLineEdit* _input;
    QPushButton* _submit;
    QString _card;

    void createLayout();
};

#endif // CARDEATER_H

#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

enum DoorStatus
{
    OPEN,
    OPENING,
    CLOSING,
    CLOSED
};

class Door : public QObject
{
    Q_OBJECT;

public:
    Door();
    ~Door() = default;

    DoorStatus getStatus() {return _status;}

public slots:
    // (Вызывается кабиной, когда нужный этаж достигнут)
    void openingSlot();

private:
    DoorStatus _status;

    QTimer _openingTimer;
    QTimer _closingTimer;
    QTimer _openedTimer;

private slots:
    // Срабатывает, когда время открытия закончилось
    void _openedSlot();
    // Срабатывает, когда время открытого состояния закончилось
    void _closingSlot();
    // Срабатывает, когда время закрытия закончилось
    void _closedSlot();

signals:
    // Сигнал испускается, когда двери переходят в состояние close
    void _closedSignal();
};

#endif

#include "door.h"
#include "controller.h"

Door::Door()
{
    _status = CLOSED;

    // Если время открытия прошло, то нужно сделать вид, что мы открылись
    QObject::connect(&_openingTimer, SIGNAL(timeout()),
                     this, SLOT(_openedSlot()));

    // Если время в открытом состоянии закончилось, то нужно начать закрываться
    QObject::connect(&_openedTimer,  SIGNAL(timeout()),
                     this, SLOT(_closingSlot()));

    // Если время закрытия прошло, то нужно сделать вид, что двери закрылись
    QObject::connect(&_closingTimer, SIGNAL(timeout()),
                     this, SLOT(_closedSlot()));
}

void Door::openingSlot()
{
    // Смотрим на диаграмму, в состояние открывания можем придти только из закрытия или процесса закрытия
    if (_status == CLOSED || _status == CLOSING)
    {
        qDebug() << "Двери открываются.";

        // Если двери закрыты, то начинаем их открывать и запускаем таймер на время открытия
        if (_status == CLOSED)
        {
            _status = OPENING;
            _openingTimer.start(DOORS_TIME);
        }
        // Если двери закрываются, то 
        else
        {
            _status = OPENING;
            // Сколько времени осталось до закрытия
            auto timer = _closingTimer.remainingTime();
            // Остановили таймер закрытия
            _closingTimer.stop();
            // Запустили таймер открытия на время равно разнице
            _openingTimer.start(DOORS_TIME - timer);
        }
    }
}

void Door::_openedSlot()
{
    if (_status == OPENING)
    {
        _status = OPEN;
        qDebug() << "Двери открыты!";
        // Пустили таймер открытого состояния
        _openedTimer.start(DOORS_TIME);
    }
}

void Door::_closingSlot()
{
    if (_status == OPEN)
    {
        _status = CLOSING;
        qDebug() << "Двери закрываются.";
        // Пустили таймер закрытия
        _closingTimer.start(DOORS_TIME);
    }
}

void Door::_closedSlot()
{
    if (_status == CLOSING)
    {
        _status = CLOSED;
        qDebug() << "Двери закрыты.";
        // Испускаем сигнал, что двери закрыты
        emit _closedSignal();
    }
}

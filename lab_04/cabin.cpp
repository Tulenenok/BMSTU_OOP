#include <QDebug>

#include "cabin.h"

Cabin::Cabin(QObject *parent) : QObject(parent)
{
    // Изначально кабина стоит
    _status = STANDING;
    // Цели нет
    _targetExist = false;

    // Сигнал перемещения -> слот перемещения
    QObject::connect(this, SIGNAL(_movingSignal()),
                     this, SLOT(_moveSlot()));

    // Время перемещения вышло -> начинаем следующее перемещение
    QObject::connect(&_moveTimer, SIGNAL(timeout()),
                     this, SLOT(_moveSlot()));

    // Открыть двери -> открыть двери
    QObject::connect(this, SIGNAL(_openDoorsSignal()),
                     &_door, SLOT(openingSlot()));

    // Закрыть -> перемещение
    QObject::connect(&_door, SIGNAL(_closedSignal()),
                     this, SLOT(_moveSlot()));
}

void Cabin::_moveSlot()
{
    // Если цель существует
    if (_targetExist)
    {
        // Если мы раньше не двигались
        if (_status == GET_TARGET || _status == STANDING)
            // Начинаем движение
            _status = MOVING;
        else
            // Прибавляем направление
            _currentFloor += _direction;

        qDebug() << "Лифт на" << _currentFloor << "этаже";

        // Если нужный этаж не достигнут запускаем таймер перемещения
        if (_currentFloor != _neededFloor)
            _moveTimer.start(MOVING_TIME);

        // Орем, что этаж достигнут, что этаж прошли, что дальше делать, аааааа
        emit _floorPassedSignal(_currentFloor, _direction);
    }
}

void Cabin::getTargetSlot(ssize_t &neededFloor, ssize_t &currentFloor)
{
    // Цель можно установить только, когда стоим
    if (_status == STANDING)
    {
        _status = GET_TARGET;
        _targetExist = true;
        _saveState(neededFloor, currentFloor);

        // Убегаем в слот перемещения
        emit _movingSignal();
    }
}

void Cabin::stoppedSlot(bool isLast, ssize_t currentFloor, ssize_t neededFloor)
{
    // Если есть цель, то останавливаться нельзя
    if (_status == MOVING || _status == STANDING)
    {
        _status = STANDING;
        _saveState(neededFloor, currentFloor);
        qDebug() << "Лифт остановился на этаже: " << _currentFloor;

        if (isLast)
            _targetExist = false;

        _moveTimer.stop();
        
        // Говорим дверям открыться
        emit _openDoorsSignal();
    }
}

void Cabin::_saveState(const ssize_t &neededFloor, const ssize_t &currentFloor)
{
    _neededFloor = neededFloor;
    _currentFloor = currentFloor;
    _direction = _currentFloor > _neededFloor ? DOWN : UP;
}

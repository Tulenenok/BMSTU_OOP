#include "elevator.h"
#include <QPalette>

Elevator::Elevator(QObject *parent) : QObject(parent)
{
    _controller.setStyleSheet("background-color:green;");

     // Связываем: если этаж достигнут -> контроллер выполняет floorPassedSlot
    QObject::connect(&_cabin, SIGNAL(_floorPassedSignal(ssize_t,Direction)),
                     &_controller, SLOT(floorPassedSlot(ssize_t,Direction)));

    // Связываем: контроллер посылает _getTargetSignal -> кабина выполняет getTargetSlot
    QObject::connect(&_controller, SIGNAL(_getTargetSignal(ssize_t&,ssize_t&)),
                     &_cabin, SLOT(getTargetSlot(ssize_t&,ssize_t&)));

    // Связываем: контроллер посылает _cabinStoppedSignal -> кабина останаливается
    QObject::connect(&_controller, SIGNAL(_cabinStoppedSignal(bool,ssize_t,ssize_t)),
                     &_cabin, SLOT(stoppedSlot(bool,ssize_t,ssize_t)));
}

QWidget *Elevator::widget()
{
    return &_controller;
}

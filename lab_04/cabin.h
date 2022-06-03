#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include "door.h"
#include "controller.h"

class Cabin : public QObject
{
    Q_OBJECT;

    enum CabinStatus
    {
        STANDING,
        GET_TARGET,
        MOVING
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() = default;

public slots:
    // Устанавливаем цель
    void getTargetSlot(ssize_t &neededFloor, ssize_t &currentFloor);
    // Останавливаем кабину
    void stoppedSlot(bool isLast, ssize_t currentFloor, ssize_t neededFloor = 1);

private:
    void _saveState(const ssize_t &neededFloor, const ssize_t &currentFloor);

    CabinStatus _status;

    Door _door;

    ssize_t _currentFloor;
    ssize_t _neededFloor;
    Direction _direction;

    bool _targetExist;

    QTimer _moveTimer;

private slots:
    void _moveSlot();

signals:
    void _floorPassedSignal(ssize_t floor, Direction dir);
    void _openDoorsSignal();
    void _movingSignal();
};

#endif

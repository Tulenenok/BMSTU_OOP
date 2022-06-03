#include "controller.h"

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    // Создай-ка нам новый слой
    _layout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);
    this->setLayout(_layout.get());

    // Обработка достижения очередного этажа
    QObject::connect(this, SIGNAL(_floorPassedSignal(ssize_t, Direction)),
                     this, SLOT(floorPassedSlot(ssize_t, Direction)));
    
    // Обработка остановки
    QObject::connect(this, SIGNAL(_controllerStoppedSignal()),
                     this, SLOT(controllerStoppedSlot()));

    _status = FREE;
    _currentFloor = 1;
    _neededFloor = 1;
    _direction = STOP;

    // Для каждого этажа
    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        // Создали кнопку
        std::shared_ptr<Button> btn(new Button);
        // Установили ей этаж
        btn->setFloor(FLOOR_COUNT - i);
        // Подписали кнопку
        btn->setText(QString::number(FLOOR_COUNT - i));

        // Добавили кнопку в массив кнопок
        _buttons.insert(_buttons.begin(), btn);
        // Добавили кнопку на слой
        _layout->addWidget(btn.get());

        // Добавили кнопку в массов посещаемых этажей
        _visitedFloors.push_back(true);

        // Соединили для этой кнопки сигнал нажатия с получением новой цели для контроллера
        QObject::connect(btn.get(), SIGNAL(pressedSignal(ssize_t)),
                         this, SLOT(newTargetSlot(ssize_t)));
    }
}

void Controller::newTargetSlot(ssize_t floor)
{
    // Надо бы посетить такой этаж
    _visitedFloors[floor - 1] = false;

    // Если мы в состоянии сейчас принять цель
    if (_status != GET_TARGET)
    {
        _status = GET_TARGET;
        _targetExist(floor);
        _neededFloor = floor;

        if (_currentFloor == _neededFloor)
            emit _floorPassedSignal(_currentFloor, _direction);
        else
        {
            _direction = _neededFloor > _currentFloor ? UP : DOWN;

            // Кабина поймает этот сигнал и начнем движение
            emit _getTargetSignal(_neededFloor, _currentFloor);
        }
    }
}

void Controller::controllerStoppedSlot()
{
    if (_status == BUSY)
    {
        _status = FREE;

        // Останавливаем кабину
        emit _cabinStoppedSignal(true, _currentFloor);
    }
}

void Controller::floorPassedSlot(ssize_t floor, Direction direction)
{
    if (_status == GET_TARGET || _status == BUSY)
    {
        _status = BUSY;
        _currentFloor = floor;
        _direction = direction;

        if (_currentFloor == _neededFloor)
        {
            _buttons[floor - 1]->unpressed();
            _visitedFloors[floor - 1] = true;

            if (_targetExist(_neededFloor))
                emit _cabinStoppedSignal(false, _currentFloor, _neededFloor);
            else
                emit _controllerStoppedSignal();
        }
    }
}

// Проверяем, есть ли еще какие-то этажи, на которые нужно сгонять
bool Controller::_targetExist(ssize_t &newFloor)
{
    int direction = _direction != STOP ? _direction : DOWN;

    for (int i = _currentFloor - 1; i >= 0 && i < FLOOR_COUNT; i += direction)
    {
        if (!_visitedFloors[i])
        {
            newFloor = i + 1;
            return true;
        }
    }

    for (int i = _currentFloor - 1; i >= 0 && i < FLOOR_COUNT; i += -direction)
    {
        if (!_visitedFloors[i])
        {
            newFloor = i + 1;
            return true;
        }
    }

    return false;
}

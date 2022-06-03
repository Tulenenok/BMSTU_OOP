#include "button.h"
#include <QDebug>

Button::Button(QWidget *parent) : QPushButton(parent)
{
    QObject::connect(this, SIGNAL(clicked()),
                     this, SLOT(_pressedSlot()));
    QObject::connect(this, SIGNAL(unpressedSignal()),
                     this, SLOT(unpressed()));

    _status = NOT_ACTIVE;
    _buttonFloor = 1;

    setStyleSheet("border-style: outset;"
                  "border-width: 2px;"
                  "border-radius: 10px;"
                  "border-color: beige;"
                  "font: bold 14px;"
                  "padding: 6px;");
}

void Button::setFloor(const ssize_t &floor)
{
    _buttonFloor = floor;
}

void Button::_pressedSlot()
{
    if (_status == NOT_ACTIVE)
    {
        // Сделали красным
        this->setStyleSheet("background-color:red;"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "border-color: beige;"
                            "font: bold 14px;"
                            "padding: 6px;");
        this->update();

        // Сказали, что кнопка сейчас нажата
        _status = ACTIVE;
        // Отключили события ввода виджета
        this->setDisabled(true);

        // Вызывали обработчик нажатия сигнала 
        emit pressedSignal(_buttonFloor);
    }
}

void Button::unpressed()
{
    if (_status == ACTIVE)
    {
        // Устанавливаем обратно зеленый
        this->setStyleSheet("background-color:green;"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "border-color: beige;"
                            "font: bold 14px;"
                            "padding: 6px;");
        this->update();

        _status = NOT_ACTIVE;

        // Возвращаем возможность ввода виджета
        this->setDisabled(false);
    }
}

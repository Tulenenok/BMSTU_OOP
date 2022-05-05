#include "../inc/BaseContainer.h"

BaseContainter::BaseContainter()
{
    this->size = 0;
}

BaseContainter::BaseContainter(const size_t size)
{
    this->size = size;
}

BaseContainter::BaseContainter(const BaseContainter &baseCont)
{
    this->size = baseCont.size;
}

BaseContainter::~BaseContainter() = default;

bool BaseContainter::isEmpty() const
{
    return this->size == 0;
}

size_t BaseContainter::getSize() const
{
    return this->size;
}


#include "../inc/BaseIter.h"

BaseIter::BaseIter()
{
    this->size = 0;
    this->cur_ind = 0;
}

BaseIter::BaseIter(const BaseIter &iter)
{
    this->size = iter.size;
    this->cur_ind = iter.cur_ind;
}

BaseIter::~BaseIter() = default;
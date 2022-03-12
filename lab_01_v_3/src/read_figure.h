#ifndef READ_FIGURE_H
#define READ_FIGURE_H

#include "stdio.h"
#include "stdlib.h"

#include "error_list.h"
#include "model.h"
#include "auxiliary_ads.h"

err_t load_figure(figure_t &figure, filename_t filename);

#endif // READ_FIGURE_H

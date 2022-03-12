#ifndef READ_FIGURE_H
#define READ_FIGURE_H

#include "stdio.h"
#include "stdlib.h"

#include "error_list.h"
#include "geom_primitives.h"

err_t read_figure(figure_t &figure, FILE *file);

#endif // READ_FIGURE_H

#ifndef CHANGE_FIGURE_H
#define CHANGE_FIGURE_H

#include "change_point.h"
#include "model.h"
#include "error_list.h"

err_t spin_figure(points_t &points, dot_t center, change_t spin_angles);

err_t scale_figure(points_t &points, dot_t center, change_t scale_koefs);

err_t move_figure(points_t &points, dot_t &center, change_t movements);

#endif // CHANGE_FIGURE_H

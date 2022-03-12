#ifndef CHANGE_POINT_H
#define CHANGE_POINT_H

#include <math.h>
#include "error_list.h"
#include "read_figure.h"
#include "auxiliary_ads.h"

err_t spin_dot(dot_t &point, dot_t center, const change_t spin_angles);

err_t move_dot(dot_t &point, const change_t move);

err_t scale_dot(dot_t &point, dot_t center, const change_t scale);


#endif // CHANGE_POINT_H

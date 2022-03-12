#ifndef DRAW_FIGURE_H
#define DRAW_FIGURE_H

#include "canvas.h" 
#include "error_list.h"
#include "model.h"

err_t draw_figure(points_t const &points, links_t const &links, canvas_t canvas);

#endif // DRAW_FIGURE_H

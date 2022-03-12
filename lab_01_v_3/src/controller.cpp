#include "controller.h"

#include "read_figure.h"
#include "draw_figure.h"
#include "change_figure.h"

err_t select_action(action_t action, event_t event)
{
    static figure_t figure = figure_init();

    err_t rc = OK;

    if (action == DRAW)
        rc = draw_figure(figure.points, figure.links, event.canvas);

    else if (action == LOAD)
        rc = load_figure(figure, event.file_name);

    else if (action == SCALE)
        rc = scale_figure(figure.points, figure.center, event.change);

    else if (action == SPIN)
        rc = spin_figure(figure.points, figure.center, event.change);

    else if (action == MOVE)
        rc = move_figure(figure.points, figure.center, event.change);

    else if (action == QUIT)
        figure_free(figure);

    else
        rc = ERR_EXTRA_ERROR;

    return rc;
}

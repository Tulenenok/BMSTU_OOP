#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "canvas.h"
#include "auxiliary_ads.h"

enum Actions {
    DRAW,
    LOAD,
    SCALE,
    SPIN,
    MOVE,
    QUIT
};

using action_t = enum Actions;

struct event_s
{
    canvas_t canvas;
    change_t change;
    filename_t file_name;
};

using event_t = struct event_s;

err_t select_action(action_t action, event_t event);

#endif // CONTROLLER_H

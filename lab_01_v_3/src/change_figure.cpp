#include "change_figure.h"

err_t spin_figure(points_t &points, dot_t center, change_t spin_angles)
{
    if (points.data == NULL)
        return ERR_NO_FIGURE;

    err_t rc = OK;

    for (int i = 0; i < points.len && rc == OK; i++)
        rc = spin_dot(points.data[i], center, spin_angles);

    return rc;
}

err_t scale_figure(points_t &points, dot_t center, change_t scale_koefs)
{
    if (points.data == NULL)
        return ERR_NO_FIGURE;

    err_t rc = OK;

    for (int i = 0; i < points.len && rc == OK; i++)
        rc = scale_dot(points.data[i], center, scale_koefs);

    return rc;
}

err_t move_figure(points_t &points, dot_t &center, change_t movements)
{
    if (points.data == NULL)
        return ERR_NO_FIGURE;

    err_t rc = OK;

    for (int i = 0; i < points.len && rc == OK; i++)
        rc = move_dot(points.data[i], movements);

    if (rc == OK)
        move_dot(center, movements);

    return rc;
}

#include "geom_primitives.h"

void points_init(points_t &points)
{
    points.data = NULL;
    points.len = 0;
}


void free_points(points_t &points)
{
    free(points.data);
    points.len = 0;
}


void links_init(links_t &links)
{
    links.data = NULL;
    links.len = 0;
}


void free_links(links_t &links)
{
    free(links.data);
    links.len = 0;
}

void center_init(dot_t &center)
{
    center.x = 0;
    center.y = 0;
    center.z = 0;
}

figure_t &figure_init(void)
{
    static figure_t figure;

    points_init(figure.points);
    center_init(figure.center);
    links_init(figure.links);

    return figure;
}

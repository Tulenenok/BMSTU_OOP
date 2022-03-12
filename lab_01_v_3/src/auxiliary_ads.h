#ifndef AUXILIARY_ADS_H
#define AUXILIARY_ADS_H

struct change_s
{
    double chg_x;
    double chg_y;
    double chg_z;
};

using change_t = struct change_s;

using filename_t = const char *;

#endif // AUXILIARY_ADS_H

#include <tfmini_driver/utils.h>

float d2f_dist(uint8_t a[2])
{
    // little endian
    int16_t data = a[1];
    data = (data << 8) | a[0];

    return ((float) data);
}

int d2i_strength(uint8_t a[2])
{
    // little endian
    int16_t data = a[1];
    data = (data << 8) | a[0];

    return ((float) data);
}

int u82i_mode(uint8_t a[1])
{
    return int(a[0]);
}


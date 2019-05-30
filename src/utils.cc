#include <sanchi_driver/utils.h>

float d2f_acc(uint8_t a[2])
{
    int16_t acc = a[0];
    acc = (acc << 8) | a[1];
    return ((float) acc) / 16384.0f;
}

float d2f_gyro(uint8_t a[2])
{
    int16_t acc = a[0];
    acc = (acc << 8) | a[1];
    return ((float) acc) / 32.8f;
}

float d2f_mag(uint8_t a[2])
{
    int16_t acc = a[0];
    acc = (acc << 8) | a[1];
    return ((float) acc) / 1.0f;
}

float d2f_euler(uint8_t a[2])
{
    int16_t acc = a[0];
    acc = (acc << 8) | a[1];
    return ((float) acc) / 10.0f;
}


double d2f_latlon(uint8_t a[4])
{
    int64_t high = a[0];
    high = (high << 8) | a[1];

    int64_t low = a[2];
    low = (low << 8) | a[3];
    return (double)((high << 8) | low);
}

double d2f_gpsvel(uint8_t a[2])
{
    int16_t acc = a[0];
    acc = (acc << 8) | a[1];
    return ((float) acc) / 10.0f;
}

float d2ieee754(uint8_t a[4])
{
    union fnum {
        float f_val;
        uint8_t d_val[4];
    } f;

    memcpy(f.d_val, a, 4);
    return f.f_val;
}

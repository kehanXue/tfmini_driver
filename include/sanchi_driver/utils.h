#ifndef UTILS_H_
#define UTILS_H_

#include <stdint.h>
#include <fcntl.h>
#include <getopt.h>
#include <poll.h>
#include <time.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <unistd.h> //  close
#include <string.h> //  strerror


float d2f_acc(uint8_t a[2]);
float d2f_gyro(uint8_t a[2]);
float d2f_mag(uint8_t a[2]);
float d2f_euler(uint8_t a[2]);
double d2f_latlon(uint8_t a[4]);
double d2f_gpsvel(uint8_t a[2]);
float d2ieee754(uint8_t a[4]);



#endif
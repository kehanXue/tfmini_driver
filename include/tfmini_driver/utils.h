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


float d2f_dist(uint8_t a[2]);
int d2i_strength(uint8_t a[2]);
int u82i_mode(uint8_t a[1]);


#endif
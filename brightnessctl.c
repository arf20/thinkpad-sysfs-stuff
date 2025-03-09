#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int get_max(const char *path) {
    int maxfd = open(path, O_RDONLY);
    if (maxfd < 0) {
        fprintf(stderr, "Error opening sysfs path: %s\n", strerror(errno));
        exit(1);
    }

    char rbuff[256];
    if (read(maxfd, rbuff, 256) < 0) {
        fprintf(stderr, "Error reading sysfs: %s\n", strerror(errno));
        exit(1);
    }

    close(maxfd);

    return atoi(rbuff);
}

int main(int argc, char **argv) {
    const char *brightnesspath = "/sys/class/backlight/intel_backlight/brightness";
    const char *maxbrightnesspath = "/sys/class/backlight/intel_backlight/max_brightness";

    if (argc < 2) {
        fprintf(stderr, "usage: %s <[0-100]|(+|-)[0-100]>\n", argv[0]);
        exit(1);
    }

    const char *arg = argv[1];

    int max = get_max(maxbrightnesspath);


    int fd = open(brightnesspath, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Error opening sysfs path: %s\n", strerror(errno));
        exit(1);
    }

    char buff[256];
    if (read(fd, buff, 256) < 0) {
        fprintf(stderr, "Error reading sysfs: %s\n", strerror(errno));
        exit(1);
    }

    int perc = 100.0f * (float)atoi(buff) / (float)max;

    if (arg[0] == '+') {
        perc += atoi(arg + 1);
    } else if (arg[0] == '-') {
        perc -= atoi(arg + 1);
    } else {
        perc = atoi(arg);
    }

    if (perc > 100) perc = 100;
    if (perc < 0) perc = 0;

    int len = snprintf(buff, 256, "%d", perc * (max / 100));

    if (write(fd, buff, len) < 1) {
        fprintf(stderr, "Error writing sysfs: %s\n", strerror(errno));
        exit(1);
    }

    close(fd);
}


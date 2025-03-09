#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <led name> [(default)toggle|on|off]\n", argv[0]);
        exit(1);
    }

    const char *ledname = argv[1];
    const char *arg = argv[2];

    char buff[256];
    snprintf(buff, 256, "/sys/class/leds/%s/brightness", ledname);

    int fd = open(buff, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Error opening sysfs path: %s\n", strerror(errno));
        exit(1);
    }

    if (argc == 2 || strcmp(arg, "toggle") == 0) {
        if (read(fd, buff, 1) < 1) {
            fprintf(stderr, "Error reading sysfs: %s\n", strerror(errno));
            exit(1);
        }

        if (write(fd, buff[0] == '1' ? "0" : "1", 1) < 1) {
            fprintf(stderr, "Error writing sysfs: %s\n", strerror(errno));
            exit(1);
        }
    } else if (strcmp(arg, "on") == 0) {
        if (write(fd, "1", 1) < 1) {
            fprintf(stderr, "Error writing sysfs: %s\n", strerror(errno));
            exit(1);
        }
    } else if (strcmp(arg, "off") == 0) {
        if (write(fd, "0", 1) < 1) {
            fprintf(stderr, "Error writing sysfs: %s\n", strerror(errno));
            exit(1);
        }
    } else {
        fprintf(stderr, "Invalid argument\n");
        exit(1);
    }

    close(fd);
}


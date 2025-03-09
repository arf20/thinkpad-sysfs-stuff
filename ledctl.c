#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <brightness path>\n");
        exit(1);
    }

    const char *ledbrpath = argv[1];
    int fd = open(ledbrpath, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Error opening sysfs path: %s\n", strerror(errno));
        exit(1);
    }

    char rbuff;
    if (read(fd, &rbuff, 1) < 1) {
        fprintf(stderr, "Error reading sysfs: %s\n", strerror(errno));
        exit(1);
    }

    if (write(fd, rbuff == '1' ? "0" : "1", 1) < 1) {
        fprintf(stderr, "Error writing sysfs: %s\n", strerror(errno));
        exit(1);
    }

    close(fd);
}


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    if ((argc < 1) || (argc > 2)) {
        fprintf(stderr, "usage: %s [0-7|auto|full-speed]\n", argv[0]);
        exit(1);
    }

    const char *arg = argv[1];

    char buff[1024];
    if (argc == 2) {
        int fd = open("/proc/acpi/ibm/fan", O_RDWR);
        if (fd < 0) {
            fprintf(stderr, "Error opening procfs path: %s\n", strerror(errno));
            exit(1);
        }

        int len = snprintf(buff, 256, "level %s", arg);

        if (write(fd, buff, len) < 0) {
            fprintf(stderr, "Error writing procfs: %s\n", strerror(errno));
            exit(1);
        }

        close(fd);
    } else {
        int fd = open("/proc/acpi/ibm/fan", O_RDONLY);
        if (fd < 0) {
            fprintf(stderr, "Error opening procfs path: %s\n", strerror(errno));
            exit(1);
        }

        int len = 0;
        if ((len = read(fd, buff, 1024)) < 0) {
            fprintf(stderr, "Error reading procfs: %s\n", strerror(errno));
            exit(1);
        }

        close(fd);

        write(STDOUT_FILENO, buff, len);
    }
    
}


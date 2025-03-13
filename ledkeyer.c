#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

const char *morse[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, " ", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    /* numbers */
    "-----",
    ".----",
    "..---",
    "...--",
    "....-",
    ".....",
    "-....",
    "--...",
    "---..",
    "----.",
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    /* letters */
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--.."
};

void on(int fd) {
    if (write(fd, "1", 1) < 1) {
        fprintf(stderr, "Error writing sysfs: %s\n", strerror(errno));
        exit(1);
    }
}

void off(int fd) {
    if (write(fd, "0", 1) < 1) {
        fprintf(stderr, "Error writing sysfs: %s\n", strerror(errno));
        exit(1);
    }
}

int main(int argc, char **argv) {
    int wpm = 20, loop = 0;
    const char *ledname = NULL, *msg = NULL;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-s") == 0) {
                wpm = atoi(argv[i + 1]);
                i++;
            } else if (strcmp(argv[i], "-l") == 0) {
                loop = 1;
            } else goto usage;
        } else {
            if (!ledname)
                ledname = argv[i];
            else if (!msg)
                msg = argv[i];
        }
    }

    if (argc < 3 || !ledname || !msg) {
usage:
        fprintf(stderr, "usage: %s [-s <wpm>] [-l] <led name> <message>\n", argv[0]);
        exit(1);
    }


    char ledpath[256];
    snprintf(ledpath, 256, "/sys/class/leds/%s/brightness", ledname);

    int fd = open(ledpath, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Error opening sysfs path: %s\n", strerror(errno));
        exit(1);
    }

    int t = 1200000 / wpm;

    while (1) {
        for (const char *cur = msg; *cur; cur++) {
            for (const char *syms = morse[toupper(*cur)]; syms && *syms; syms++) {
                switch (*syms) {
                    case '.': { 
                        on(fd);
                        usleep(t);
                        off(fd);
                        usleep(t);
                    } break;
                    case '-': {
                        on(fd);
                        usleep(3*t);
                        off(fd);
                        usleep(t);
                    } break;
                    case ' ': {
                        usleep(4*t);
                    }
                }
            }
            usleep(2*t);
        }
        if (!loop)
            break;
    }

    close(fd);

    return 0;
}


CC := gcc
CFLAGS := -Wall -pedantic -g -O0
LDFLAGS :=

all: ledctl brightnessctl

ledctl: ledctl.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

brightnessctl: brightnessctl.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

.PHONY: clean
clean:
	rm -f ledctl brightnessctl


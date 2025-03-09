CC := gcc
CFLAGS := -Wall -pedantic -g -O0
LDFLAGS :=

all: ledctl brightnessctl

ledctl: ledctl.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

brightnessctl: brightnessctl.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

.PHONY: clean install
clean:
	rm -f ledctl brightnessctl

install:
	cp ledctl brightnessctl /usr/local/bin
	chown root:root /usr/local/bin/ledctl /usr/local/bin/brightnessctl
	chmod a+s /usr/local/bin/ledctl /usr/local/bin/brightnessctl



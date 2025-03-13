CC := gcc
CFLAGS := -Wall -pedantic -g -O0
LDFLAGS :=

all: ledctl brightnessctl fanctl ledkeyer

ledctl: ledctl.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

brightnessctl: brightnessctl.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

fanctl: fanctl.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

ledkeyer: ledkeyer.c
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS)

.PHONY: clean install
clean:
	rm -f ledctl brightnessctl fanctl

install:
	cp ledctl brightnessctl fanctl ledkeyer thinkhotkeys /usr/local/bin
	chown root:root /usr/local/bin/ledctl /usr/local/bin/brightnessctl /usr/local/bin/fanctl /usr/local/bin/ledkeyer
	chmod a+s /usr/local/bin/ledctl /usr/local/bin/brightnessctl /usr/local/bin/fanctl /usr/local/bin/ledkeyer


CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS := -lm -lcrypto
SOURCES := $(wildcard q*.c)
TARGETS := $(patsubst q%.c,build/q%,$(SOURCES))

.PHONY: all clean
all: $(TARGETS)

build/q%: q%.c cryptoutils.h des_schedule.h sdes.h
	@mkdir -p build
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -rf build

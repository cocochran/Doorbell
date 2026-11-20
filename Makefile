CC      := gcc
TARGET  := doorbell
SRCS    := main.c client.c
OBJS    := $(SRCS:.c=.o)
DEPS    := $(OBJS:.o=.d)

CFLAGS  := -std=gnu23 -Wall -Wextra -g $(shell pkg-config --cflags gtk4)
LDLIBS  := $(shell pkg-config --libs gtk4) -lpaho-mqtt3c

.PHONY: all clean FORCE

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Every object may include client.h, so make sure it exists first.
$(OBJS): client.h

# Regenerated on every make from the function definitions in client.c.
# Only replaced when its contents change, so unchanged builds don't recompile.
client.h: FORCE
	@{ \
		echo '/* Generated from client.c by make. Do not edit. */'; \
		echo '#ifndef CLIENT_H'; \
		echo '#define CLIENT_H'; \
		echo; \
		grep -E '^#include[[:space:]]+"' client.c | grep -v '"client.h"'; \
		echo; \
		awk '/^[A-Za-z_][^;#=]*\)[[:space:]]*\{[[:space:]]*$$/ && !/^static/ && !/[[:space:]]main[[:space:]]*\(/ { \
			sub(/[[:space:]]*\{[[:space:]]*$$/, ";"); print }' client.c; \
		echo; \
		echo '#endif'; \
	} > $@.tmp
	@if cmp -s $@.tmp $@; then rm -f $@.tmp; else mv $@.tmp $@; echo "Generated $@"; fi

FORCE:

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS) client.h client.h.tmp

-include $(DEPS)

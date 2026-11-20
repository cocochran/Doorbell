CC      := gcc
TARGET  := doorbell
SRCDIR  := .
SRCS    := $(SRCDIR)/main.c $(SRCDIR)/client.c
OBJS    := $(SRCS:.c=.o)
DEPS    := $(OBJS:.o=.d)

CFLAGS  := -std=gnu2x -I. -I$(SRCDIR) -Wall -Wextra -g $(shell pkg-config --cflags gtk4)
LDLIBS  := $(shell pkg-config --libs gtk4) -lpaho-mqtt3c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Every object may include client.h, so make sure it exists first.
$(OBJS): $(SRCDIR)/client.h

# Regenerated from the function definitions in client.c whenever client.c changes.
$(SRCDIR)/client.h: $(SRCDIR)/client.c
	@echo "Generating $@"
	@{ \
		echo '/* Generated from client.c by make. Do not edit. */'; \
		echo '#ifndef CLIENT_H'; \
		echo '#define CLIENT_H'; \
		echo; \
		grep -E '^#include[[:space:]]+"' $(SRCDIR)/client.c | grep -v '"client.h"'; \
		echo; \
		awk '/^[A-Za-z_][^;#=]*\)[[:space:]]*\{[[:space:]]*$$/ && !/^static/ && !/[[:space:]]main[[:space:]]*\(/ { \
			sub(/[[:space:]]*\{[[:space:]]*$$/, ";"); print }' $(SRCDIR)/client.c; \
		echo; \
		echo '#endif'; \
	} > $@

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS) $(SRCDIR)/client.h

-include $(DEPS)

CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic
LDFLAGS ?=

TARGET := hexdump
SRCS := main.c hexdump.c
OBJS := $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

main.o: main.c hexdump.h
hexdump.o: hexdump.c hexdump.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

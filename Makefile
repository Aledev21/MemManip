CC := gcc
CFLAGS := -Wall $(shell pkg-config --cflags gtk+-3.0)
LIBS := $(shell pkg-config --libs gtk+-3.0)
EXECUTABLE := memory_manager
SRCS := memory_manager.c main.c  
OBJS := $(SRCS:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c memory_manager.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean

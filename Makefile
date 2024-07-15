# Makefile para compilar o Memory Manager com GTK e MinGW-64 no Linux

CC := x86_64-w64-mingw32-gcc

CFLAGS := -Wall $(shell pkg-config --cflags gtk+-3.0)


LIBS := $(shell pkg-config --libs gtk+-3.0)


EXECUTABLE := memory_manager.exe


SRCS := memory_manager.c main.c


OBJS := $(SRCS:.c=.o)


all: $(EXECUTABLE)

l
$(EXECUTABLE): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^ $(LIBS)


%.o: %.c
    $(CC) $(CFLAGS) -c -o $@ $<


clean:
    rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean

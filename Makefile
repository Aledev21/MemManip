CC = gcc
CFLAGS = -Wall -Wextra -std=c17
LIBS = `pkg-config --cflags --libs gtk+-3.0`

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

EXEC = memory_manager

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LIBS) -I$(SRC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

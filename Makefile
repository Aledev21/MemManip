CC = gcc
CFLAGS = -Wall -Wextra -std=c17 $(shell pkg-config --cflags gtk+-3.0)
LIBS = $(shell pkg-config --libs gtk+-3.0)

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

EXEC = memory_manager

.PHONY: all check-deps clean

all: check-deps $(EXEC)

check-deps:
	@command -v pkg-config >/dev/null 2>&1 || { echo "pkg-config não está instalado. Instalando..."; sudo apt-get install -y pkg-config; }
	@pkg-config --atleast-version=3.0 gtk+-3.0 >/dev/null 2>&1 || { echo "GTK+ 3.0 não está instalado. Instalando..."; sudo apt-get install -y libgtk-3-dev; }

$(EXEC): $(OBJ)
	$(CC) $^ $(LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

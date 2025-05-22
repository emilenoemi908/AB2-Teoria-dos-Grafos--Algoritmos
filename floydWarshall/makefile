INCLUDE_DIR = headers
SRC_DIR = algoritmo
BUILD_DIR = build
BIN = $(BUILD_DIR)/floydWarshall

CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/floydWarshall.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/floydWarshall.h
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(BIN)

run: $(BIN)
	$(BIN)
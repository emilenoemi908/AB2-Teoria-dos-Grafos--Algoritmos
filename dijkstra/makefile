INCLUDE_DIR = headers
SRC_DIR = algoritmo.
BUILD_DIR= build
BIN = djikstra

cc = gcc
CFLAGS = -Wall  -I$(INCLUDE_DIR)

SRCS= $(SRC_DIR)/main.c $(SRC_DIR)/djikstra.c

OBJS= $(SRCS: $ (SRC_DIR)/%.C= $(BUILD_DIR)/%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/prim.h
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f $(SRC_DIR)/*.o $(BIN)

run: $(BIN)
	./$(BIN)

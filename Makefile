CC = gcc
CFLAGS = -O2

BUILD_DIR = ./build
EXEC_FILE = raycasting


all: debug

debug: $(BUILD_DIR)/main.o $(BUILD_DIR)/socket.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/socket.o -o $(EXEC_FILE)

$(BUILD_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/socket.o: socket.c socket.h
	$(CC) $(CFLAGS) -c socket.c -o $(BUILD_DIR)/socket.o

clean:
	rm $(BUILD_DIR)/*.o $(EXEC_FILE)

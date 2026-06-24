CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -pthread
DEBUG=-g

TARGET_NAME := goblinnet
SRC_DIR     := src
BUILD_DIR   := build
BIN_DIR     := bin

TARGET := $(BIN_DIR)/$(TARGET_NAME)
OBJ    := $(BUILD_DIR)/goblinnet.o

.DEFAULT_GOAL := $(TARGET)
.PHONY: debug clean

$(TARGET): $(OBJ) $(RES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ): $(SRC_DIR)/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

	
debug: CFLAGS += $(DEBUG)
debug: $(TARGET)

clean:
	rm $(BUILD_DIR) rm $(BIN_DIR)
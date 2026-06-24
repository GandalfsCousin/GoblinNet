CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -pthread
DEBUG=-g

TARGET_NAME := goblinnet
SRC_DIR     := src
BUILD_DIR   := build
BIN_DIR     := bin

TARGET := $(BIN_DIR)/$(TARGET_NAME)
OBJ    := $(BUILD_DIR)/goblinnet.o
RES := $(BUILD_DIR)/icon.o

.DEFAULT_GOAL := $(TARGET)
.PHONY: debug clean

$(TARGET): $(OBJ) $(RES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ): $(SRC_DIR)/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(RES): resources/icon.rc resources/goblinnet.ico | $(BUILD_DIR)
	windres $< -O coff -o $@

$(BUILD_DIR):
	if not exist $@ mkdir $@

$(BIN_DIR):
	if not exist $@ mkdir $@

	
debug: CFLAGS += $(DEBUG)
debug: $(TARGET)

clean:
	if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
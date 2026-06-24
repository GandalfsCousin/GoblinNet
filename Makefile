CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -pthread -Iinclude
DEBUG=-g

TARGET_NAME := goblinnet
SRC_DIR     := src
BUILD_DIR   := build
BIN_DIR     := bin

TARGET := $(BIN_DIR)/$(TARGET_NAME)
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

.DEFAULT_GOAL := $(TARGET)
.PHONY: debug clean

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

debug: CFLAGS += $(DEBUG)
debug: $(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
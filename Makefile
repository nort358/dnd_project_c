CC ?= clang
CFLAGS_DEBUG   := -std=c17 -Wall -Wextra -Werror=implicit-function-declaration -O0 -g
CFLAGS_RELEASE := -std=c17 -Wall -Wextra -O2 -DNDEBUG
BUILD_DIR := build
TARGET := $(BUILD_DIR)/app
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))
INCLUDES := -Iinclude

.PHONY: all run clean dirs

all: dirs $(TARGET)

dirs:
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c | dirs
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

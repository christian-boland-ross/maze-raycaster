CC = gcc

CFLAGS = -Wall -Wextra -g
LDLIBS = -lm

SRC_DIR = source
GRAPHICS_DIR = graphics
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.c) $(GRAPHICS_DIR)/graphics.c

TARGET = maze

TEXTURE_SET ?= default
MAZE_SIZE ?= 10

MAZE_SIZE_VALID := $(shell test "$(MAZE_SIZE)" -ge 3 2>/dev/null && test "$(MAZE_SIZE)" -le 100 2>/dev/null && echo yes)
ifneq ($(MAZE_SIZE_VALID),yes)
$(error MAZE_SIZE must be an integer between 3 and 100)
endif

.PHONY: all clean run FORCE

all: $(TARGET)

$(TARGET): $(SOURCES) FORCE
	$(CC) $(CFLAGS) -DGRID_SIZE=$(MAZE_SIZE) -I$(GRAPHICS_DIR) -I$(INCLUDE_DIR) $(SOURCES) -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	TEXTURE_SET=$(TEXTURE_SET) ./$(TARGET) | java -jar $(GRAPHICS_DIR)/drawapp-5.0.jar

clean:
	rm -f $(TARGET)

FORCE:
CC = gcc

CFLAGS = -Wall -Wextra -g
LDLIBS = -lm

SRC_DIR = source
GRAPHICS_DIR = graphics
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.c) $(GRAPHICS_DIR)/graphics.c

ifeq ($(OS),Windows_NT)
TARGET = maze.exe
ifneq ($(filter sh sh.exe bash bash.exe dash dash.exe,$(notdir $(SHELL))),)
WINDOWS_CMD_SHELL =
else
WINDOWS_CMD_SHELL = yes
endif
else
TARGET = maze
endif

TEXTURE_SET ?= default
MAZE_SIZE ?= 10

.PHONY: all clean run FORCE

all: $(TARGET)

$(TARGET): $(SOURCES) FORCE
	$(CC) $(CFLAGS) -DGRID_SIZE=$(MAZE_SIZE) -I$(GRAPHICS_DIR) -I$(INCLUDE_DIR) $(SOURCES) -o $(TARGET) $(LDLIBS)

ifeq ($(WINDOWS_CMD_SHELL),yes)
run: $(TARGET)
	set "TEXTURE_SET=$(TEXTURE_SET)" && .\$(TARGET) | java -jar $(GRAPHICS_DIR)/drawapp-5.0.jar

clean:
	if exist $(TARGET) del /Q $(TARGET)
else
run: $(TARGET)
	TEXTURE_SET=$(TEXTURE_SET) ./$(TARGET) | java -jar $(GRAPHICS_DIR)/drawapp-5.0.jar

clean:
	rm -f $(TARGET)
endif

FORCE:
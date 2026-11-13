CC = gcc

CFLAGS = -Wall -Wextra -g
LDLIBS = -lm

SRC_DIR = source
GRAPHICS_DIR = graphics
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.c) $(GRAPHICS_DIR)/graphics.c

TARGET = maze

TEXTURE_SET ?= default

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -I$(GRAPHICS_DIR) -I$(INCLUDE_DIR) $(SOURCES) -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	TEXTURE_SET=$(TEXTURE_SET) ./$(TARGET) | java -jar $(GRAPHICS_DIR)/drawapp-5.0.jar

clean:
	rm -f $(TARGET)
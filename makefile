# OBJECTS=main.o lc55.o lc1306.o interval_list_intersections.o
BUILD_DIR=build/
SOURCE_DIR=src/
OBJECTS:=$(patsubst $(SOURCE_DIR)%.cpp,%.o,$(wildcard $(SOURCE_DIR)*.cpp))
TARGET=build/target
CC=clang++
PCH_H=inc.hpp
PCH=$(BUILD_DIR)$(PCH_H).pch
CFLAGS=-g -Wall -std=c++17
LIBS=

OBJECT_FILES:=$(addprefix $(BUILD_DIR), $(OBJECTS))

all: $(BUILD_DIR) $(PCH) $(OBJECT_FILES) $(TARGET)
run: | $(BUILD_DIR) $(TARGET)
	./$(TARGET)
clean:
	-rm -r -f $(PCH) $(OBJECT_FILES) $(TARGET) $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(PCH) : $(PCH_H)
	$(CC) -o $@ $^ $(CFLAGS)

$(TARGET) : $(OBJECT_FILES)
	$(CC) -o $@ $^ $(LIBS)

$(OBJECT_FILES) : $(BUILD_DIR)%.o : $(SOURCE_DIR)%.cpp $(PCH)
	$(CC) -c -o $@ $< -include-pch $(PCH) $(CFLAGS)
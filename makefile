BUILD_DIR=build/
SOURCE_DIR=src/
EXES:=$(patsubst $(SOURCE_DIR)%.cpp,%,$(wildcard $(SOURCE_DIR)*.cpp))
CC=clang++
PCH_H=stdafx.hpp
PCH=$(BUILD_DIR)$(PCH_H).pch
DEPEND_HEADERS:=$(PCH_H) inc.hpp
CFLAGS=-g -Wall -std=c++17
LIBS=-lCatch2Main -lCatch2

EXE_FILES:=$(addprefix $(BUILD_DIR), $(EXES))

all: $(EXE_FILES)

run: $(EXES)

clean:
	-rm -r -f $(PCH) $(EXE_FILES) $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(PCH) : $(PCH_H)
	$(CC) -o $@ $^ $(CFLAGS)

$(EXES) : % : $(BUILD_DIR)%
	./$^

$(EXE_FILES) : $(BUILD_DIR)% : $(SOURCE_DIR)%.cpp $(DEPEND_HEADERS) | $(BUILD_DIR) $(PCH)
	$(CC) -o $@ $< -include-pch $(PCH) $(CFLAGS) $(LIBS)

SHELL := bash
CC := g++

# General directories
SRC_D := src
OBJ_D := obj
INC_D := include
BIN_D := bin
LIB_D := third_party
TESTS_D := tests


CFLAGS := -Wall -Wextra -Wpedantic 
CPPFLAGS := -std=c++17 -I$(SRC_D) -I$(LIB_D) -I$(INC_D)
LIBS := -L$(LIB_D) $(LIB_D)/glad/glad.a -lglfw -ldl


SRC_FILES = $(shell find $(SRC_D) -type f -name "*.cpp" ! -name "*main.cpp")
OBJECTS := $(SRC_FILES:$(SRC_D)/%.cpp=%.o)
OBJECTS := $(addprefix $(OBJ_D)/, $(OBJECTS))


TESTS_FILES = $(shell find $(TESTS_D) -type f -name "*[!main.cpp].cpp")



$(BIN_D)/tetris: $(SRC_D)/main.cpp $(OBJECTS)
	@[ -d $(shell dirname $@) ] || mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^  $(LIBS)

$(BIN_D)/tests: $(TESTS_D)/main.cpp $(TESTS_FILES) $(OBJECTS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LIBS)

clean:
	@rm -rv $(BIN_D)/tetris $(OBJ_D)/*


$(OBJ_D)/%.o: $(SRC_D)/%.cpp
	@[ -d $(shell dirname $@) ] || mkdir -p $(shell dirname $@)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

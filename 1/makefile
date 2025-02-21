CC=g++
CC_FLAGS=-std=c++11 -Werror -Wall -Wextra -pedantic

BUILD_DIR=build
SRC_DIR=src

CPPCHECK_FLAGS=--enable=all --inconclusive --std=c++11 --language=c++ --suppress=missingIncludeSystem --check-level=exhaustive
CPPLINT_FLAGS=--linelength=120 --filter=-whitespace/line_length,-whitespace/comments,-whitespace/braces,-whitespace/parens,-whitespace/newline,-whitespace/operators,-whitespace/semicolon,-whitespace/indent,-whitespace/labels,-whitespace/empty_conditional_body,-whitespace/empty_loop_body,-whitespace/end_of_line,-whitespace/blank_line,-whitespace/comma,-whitespace/braces,-whitespace/parens,-whitespace/comments,-whitespace/semicolon,-whitespace/operators,-whitespace/indent,-whitespace/labels,-whitespace/empty_conditional_body,-whitespace/empty_loop_body,-whitespace/end_of_line,-whitespace/blank_line,-whitespace/comma

all: $(BUILD_DIR)/main.o $(BUILD_DIR)/sort.o
	$(CC) $^ -o $(BUILD_DIR)/main

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(BUILD_DIR) check
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/sort.o: $(SRC_DIR)/sort.cpp $(SRC_DIR)/sort.h $(BUILD_DIR) check
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/sort.cpp -o $(BUILD_DIR)/sort.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*

run:
	./$(BUILD_DIR)/main

check:
	cppcheck $(CPPCHECK_FLAGS) $(SRC_DIR)/*.cpp
	cpplint $(CPPLINT_FLAGS) $(SRC_DIR)/*.cpp
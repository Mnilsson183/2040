CC=g++
CC_FLAGS=-std=c++11 -Wall -Wextra -pedantic

BUILD_DIR=build
SRC_DIR=src

all: $(BUILD_DIR)/main.o $(BUILD_DIR)/bubble_sort.o $(BUILD_DIR)/insertion_sort.o $(BUILD_DIR)/selection_sort.o $(BUILD_DIR)/quick_sort.o $(BUILD_DIR)/merge_sort.o
	$(CC) $^ -o $(BUILD_DIR)/main

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/bubble_sort.o: $(SRC_DIR)/bubble_sort.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/bubble_sort.cpp -o $(BUILD_DIR)/bubble_sort.o

$(BUILD_DIR)/insertion_sort.o: $(SRC_DIR)/insertion_sort.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/insertion_sort.cpp -o $(BUILD_DIR)/insertion_sort.o

$(BUILD_DIR)/selection_sort.o: $(SRC_DIR)/selection_sort.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/selection_sort.cpp -o $(BUILD_DIR)/selection_sort.o

$(BUILD_DIR)/quick_sort.o: $(SRC_DIR)/quick_sort.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/quick_sort.cpp -o $(BUILD_DIR)/quick_sort.o

$(BUILD_DIR)/merge_sort.o: $(SRC_DIR)/merge_sort.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/merge_sort.cpp -o $(BUILD_DIR)/merge_sort.o

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/main $(BUILD_DIR)/a.out

run:
	./$(BUILD_DIR)/main
CC=g++
CPP_FLAGS=-std=c++11 -Wall -Wextra -pedantic

BUILD_DIR=build
EXE=$(BUILD_DIR)/a.out
FILES= Dijkstra.cpp edge.cpp Graph.cpp List_Graph.cpp Matrix_Graph.cpp

all: $(FILES) $(BUILD_DIR)
	$(CC) $(CPP_FLAGS) $(FILES) -o $(EXE)

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*

test:
	# Run the program on the three sample files
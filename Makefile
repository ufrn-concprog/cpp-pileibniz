CXX ?= c++
CXXFLAGS ?= -Wall -Wextra -pedantic -std=c++20 -pthread -Iinclude

BIN_DIR := bin
BUILD_DIR := build
PROGRAM := $(BIN_DIR)/pileibniz
OBJECTS := $(BUILD_DIR)/main.o $(BUILD_DIR)/calc_thread.o
DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/calc_thread.o: src/calc_thread.cpp include/calc_thread.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

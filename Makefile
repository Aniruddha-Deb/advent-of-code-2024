CC := g++-14
CFLAGS := -std=gnu++23 -Wall -O2 -fopenmp
BIN_DIR := bin
SRC_DIR := src
INPUT_DIR := input
SHELL := /bin/bash

.PRECIOUS: $(BIN_DIR)/day%

$(BIN_DIR)/day%: $(SRC_DIR)/day%.cpp
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

run-%: $(BIN_DIR)/day% $(INPUT_DIR)/day%.txt
	./$(BIN_DIR)/day$* < $(INPUT_DIR)/day$*.txt

run2-%: $(BIN_DIR)/day%_2 $(INPUT_DIR)/day%.txt
	./$(BIN_DIR)/day$*_2 < $(INPUT_DIR)/day$*.txt

test-%: $(BIN_DIR)/day% $(INPUT_DIR)/test%.txt
	./$(BIN_DIR)/day$* < $(INPUT_DIR)/test$*.txt

test2-%: $(BIN_DIR)/day%_2 $(INPUT_DIR)/test%.txt
	./$(BIN_DIR)/day$*_2 < $(INPUT_DIR)/test$*.txt

fetch-%:
	export $$(cat .env | xargs) && \
	curl -v --cookie "$$AOC24_COOKIE" https://adventofcode.com/2024/day/$*/input -o input/day$*.txt

setup:
	mkdir bin input

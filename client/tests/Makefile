SRC = ./*
INC = .
BIN = bin

TARGET = $(BIN)/controllerTester
SOURCE := $(wildcard $(SRC)/*.cpp)
OBJECT := $(patsubst %,$(BIN)/%, $(notdir $(addsuffix .o,$(basename $(SOURCE)))))

CC=g++
CFLAGS = -std=c++11 -Wall -g -pedantic -I $(INC)

RED = \e[1;31m
GREEN = \e[1;32m
YELLOW = \e[1;33m
BLUE = \e[1;34m
NO_COLOR = \e[1;0m

all: bin $(TARGET)

bin:
	mkdir -pv bin

$(TARGET): $(OBJECT)
	@echo -e "$(GREEN)Linking...$(NO_COLOR)"
	$(CC) $^ -o $@
	@echo -e "$(GREEN)Done$(NO_COLOR)"

$(BIN)/%.o: $(SRC)/%.cpp
	@echo -e "$(GREEN)Compiling$(NO_COLOR)"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: bin all test clean help

test: all
	./$(TARGET)

clean:
	rm -rf bin

help:
	@echo -e "$(GREEN)target: $(BLUE)$(TARGET)$(NO_COLOR)"
	@echo -e "$(GREEN)src: $(BLUE)$(SOURCE)$(NO_COLOR)"
	@echo -e "$(GREEN)obj: $(BLUE)$(OBJECT)$(NO_COLOR)"
	@echo -e "$(YELLOW)compile: $(BLUE)$(CC) $(CFLAGS) -c $(GREEN)src$(BLUE) -o $(GREEN)obj$(NO_COLOR)"
	@echo -e "$(YELLOW)link: $(BLUE)$(CC) $(GREEN)obj$(BLUE) -o $(GREEN)target$(BLUE)$(NO_COLOR)"
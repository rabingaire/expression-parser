TARGET = ex

CC = clang++

CFLAGS = -Wall -Werror -Wunused-value -std=c++17 -g -DDEBUG_LEXER -DDEBUG_PARSER

HEADERS=$(shell find . -type f -name "*.hpp")
SOURCE=$(shell find . -type f -name "*.cpp")
OBJS=$(SOURCE:.cpp=.o)

%.o: %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $<

all: build clean-objs

build: $(OBJS) $(HEADERS)
	@$(CC) -o $(TARGET) $(OBJS)

clean-objs:
	@rm -f $(OBJS)

.PHONY: clean
clean: clean-objs
	@rm -f ./$(TARGET)

TARGET = ex

CC = clang++

CFLAGS = -Wall -Werror -Wunused-value -std=c++17 -g -DDEBUG_LEXER

HEADERS=$(shell find . -type f -name "*.hpp")
SOURCE=$(shell find . -type f -name "*.cpp")
OBJS=$(SOURCE:.cpp=.o)

%.o: %.cpp
	@$(CC) $(CFLAGS) -o $@ -c $<

build: $(OBJS) $(HEADERS)
	@$(CC) -o $(TARGET) $(OBJS)

.PHONY: clean
clean:
	@rm -f $(OBJS)
	@rm -f ./$(TARGET)

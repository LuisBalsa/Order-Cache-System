CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -pthread

TARGET = book

SRCS = main.cpp OrderCache.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

re: clean all

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

sanitize: CXXFLAGS += -fsanitize=thread -g
sanitize: re
	./$(TARGET)

.PHONY: all clean

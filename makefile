CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17
TARGET := hacker-rm
SRC := hacker-rm.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
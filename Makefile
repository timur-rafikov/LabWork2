CXX = g++
CXXFLAGS = -Wall -g
TESTFLAGS = -lgtest -lgmock -pthread

TEST_SRC = tests/test.cpp src/player.cpp
TEST_TARGET = test-game

TARGET = game
OBJ = src/main.o src/modes.o src/player.o
SRC = src/main.cpp src/modes.cpp src/player.cpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

all: $(TARGET)

test: $(TEST_SRC)
	$(CXX) $(TEST_SRC) $(CXXFLAGS) -o $(TEST_TARGET) $(TESTFLAGS)

clean_test:
	rm -f $(TEST_TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean clean_test

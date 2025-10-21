CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++20 -O2 
LIBS := -lsfml-graphics -lsfml-window -lsfml-system
TARGET := fluid_sim
SRC := main.cpp aux-functions.cpp initializations.cpp
OBJ := $(SRC:.cpp=.o)
DEPS := constants.hpp aux-functions.hpp initializations.hpp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild

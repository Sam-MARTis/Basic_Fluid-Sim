
CXX ?= g++
NVCC ?= nvcc
SFML_CFLAGS := $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
SFML_LIBS := $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

CXXFLAGS := -Wall -std=c++20 -O2 \
            $(SFML_CFLAGS) \
            -Iimgui \
            -Iimgui-sfml

NVCCFLAGS := -O2 -arch=sm_86

LDFLAGS :=
LIBS := $(SFML_LIBS) -lGL -lpthread -ldl

TARGET := fluid_sim

SRC := main.cpp \
       imgui/imgui.cpp \
       imgui/imgui_widgets.cpp \
       imgui/imgui_draw.cpp \
       imgui/imgui_tables.cpp \
       imgui-sfml/imgui-SFML.cpp \
       aux-functions.cpp \
       initializations.cpp \
	display-functions.cpp \
       core-sim-functions.cpp

CUDA_SRC := kernel.cu

DEPS := constants.hpp aux-functions.hpp initializations.hpp display-functions.hpp core-sim-functions.hpp

OBJ := $(SRC:.cpp=.o)
CUDA_OBJ := $(CUDA_SRC:.cu=.o)

all: $(TARGET)

$(TARGET): $(OBJ) $(CUDA_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS) -lcuda -lcudart

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(CUDA_OBJ) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild


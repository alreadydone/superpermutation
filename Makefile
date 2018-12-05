APP = superp 
CXX = g++
FLAGS = -std=c++17 -O3 -Wall 
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

.PHONY: all

all: $(APP)

$(APP): $(OBJ)
	$(CXX) $(FLAGS) $(OBJ) -o $@
%.o: %.cpp 
	$(CXX) $(FLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ) $(APP)

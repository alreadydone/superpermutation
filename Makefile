APP = superp 
APP3 = egan
CXX = g++
CC = gcc
FLAGS = -std=c++17 -O3 -Wall 
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

.PHONY: all clean

all: $(APP) $(APP3)

$(APP): $(OBJ)
	$(CXX) $(FLAGS) $(OBJ) -o $@
$(APP3): $(APP3:=.c)
	$(CC) $< -o $@
%.o: %.cpp 
	$(CXX) $(FLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ) $(APP) $(APP3)

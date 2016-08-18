# WARNING: Do not modify this file.
CXX = g++
CXXFLAGS = -c -std=c++0x
SRCS = Cookbook.cpp Equipment.cpp Ingredient.cpp Inventory.cpp Parser.cpp Preparation.cpp Recipe.cpp Main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = Cookbook.h Equipment.h Ingredient.h Inventory.h Parser.h Preparation.h Recipe.h
EXEC = Proj3

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ 

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $<

clean: 
	rm -rf *.o Proj3

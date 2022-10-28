CPP = g++
STD = -std=c++17
EXE = game.out

LIBS = . ./lib
INCLUDES = . ./include/ 
FLAGS = $(foreach dir,$(INCLUDES), -I$(dir))
CPFILES = $(foreach dir,$(LIBS),$(wildcard $(dir)/*.cpp))

OBJECTS =  $(patsubst %.cpp,%.o,$(CPFILES))

all: clean build

%.o:%.cpp
	$(CPP) $(STD) -c -o $@ $^ $(FLAGS)


build: $(OBJECTS)
	$(CPP) $(STD) $(OBJECTS) -o $(EXE)     

clean:
	rm -f ./*.o
	rm -f ./*/*.o
	rm -f ./$(EXE)



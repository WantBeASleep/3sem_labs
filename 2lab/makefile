PREF_MAIN = ./main/

MAIN = $(wildcard $(PREF_MAIN)*.cpp)
MAIN_O = $(patsubst $(PREF_MAIN)%.cpp, %.o, $(MAIN))

all:
	g++ -c main.cpp $(MAIN)
	g++ -o exe main.o $(MAIN_O)
	rm *.o
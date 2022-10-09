# PREF_CFG = ./cfg/
# PREF_LIB = ./lib/
# PREF_SEQ = ./seq/
# PREF_SORT = ./sort/
# PREF_SRC = ./src/
PREF_MAIN = ./main/

# CFG = $(wildcard $(PREF_CFG)*.cpp)
# CFG_O = $(patsubst $(PREF_CFG)%.cpp, %.o, $(CFG))

# LIB = $(wildcard $(PREF_LIB)*.cpp)
# LIB_O = $(patsubst $(PREF_LIB)%.cpp, %.o, $(LIB))

# SEQ = $(wildcard $(PREF_SEQ)*.cpp)
# SEQ_O = $(patsubst $(PREF_SEQ)%.cpp, %.o, $(SEQ))

# SORT = $(wildcard $(PREF_SORT)*.cpp)
# SORT_O = $(patsubst $(PREF_SORT)%.cpp, %.o, $(SORT))

# SRC = $(wildcard $(PREF_SRC)*.cpp)
# SRC_O = $(patsubst $(PREF_SRC)%.cpp, %.o, $(SRC))

MAIN = $(wildcard $(PREF_MAIN)*.cpp)
MAIN_O = $(patsubst $(PREF_MAIN)%.cpp, %.o, $(MAIN))

all:
	g++ -c main.cpp $(MAIN)
	g++ -o exe main.o $(MAIN_O)
	rm *.o
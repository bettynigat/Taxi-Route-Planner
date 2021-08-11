CXX      = g++ --std=c++11
CXXFLAGS = -W -Wall -O2

TARGETS = mapgen pathfinder
SRC_MAPGEN = src/mapgen.cpp src/map.cpp
OBJ_MAPGEN = $(patsubst %.cpp,%.o,$(SRC_MAPGEN))
SRC_PATHFINDER = src/pathfinder.cpp src/map.cpp
OBJ_PATHFINDER = $(patsubst %.cpp,%.o,$(SRC_PATHFINDER))


all: $(TARGETS)

.PHONY: clean

mapgen: $(OBJ_MAPGEN)
	$(CXX) $(CXXFLAGS) -o $@ $^

pathfinder: $(OBJ_PATHFINDER)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(TARGETS) $(OBJ_MAPGEN) $(OBJ_PATHFINDER)

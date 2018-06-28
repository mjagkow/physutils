EXECUTABLE=updateTree

all: $(EXECUTABLE)

$(EXECUTABLE):
	@g++ -o updateTree updateTree.cpp pdgid.cpp --std=c++11 `root-config --cflags --libs` -lTreePlayer -O3

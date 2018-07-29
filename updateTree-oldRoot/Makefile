EXECUTABLE=updateTree

SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)
EXECUTABLE = updateTree
PHONY = clean cleanup
LD = g++
CC = g++
CFLAGS = -O3 $(shell root-config --cflags) -m64 -pthread -MD -MP -ggdb
LFLAGS = $(shell root-config --libs)

all: $(EXECUTABLE)

-include $(SOURCES:%.cpp=%.d)

.PHONY: $(PHONY)

%.o : %.cpp
	$(CC) --std=c++11 $(CFLAGS) -o $@ -c $<

$(EXECUTABLE): $(OBJS)
	$(LD) -o $@ $(LFLAGS) $^

cleanup:
	@rm -f *.o
	@rm -f *.d

clean: cleanup
	@rm -f $(EXECUTABLE)

rebuild: clean $(EXECUTABLE)

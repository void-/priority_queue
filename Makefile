.RECIPEPREFIX = >

CC = g++
CXXFLAGS = -std=c++0x
BINARY = "check"

test: test.cpp priority_queue.h priority_queue.hxx
> $(CC) $(CXXFLAGS) test.cpp -o $(BINARY)
check: test
> ./$(BINARY)

.PHONY: clean
clean:
> rm $(BINARY)

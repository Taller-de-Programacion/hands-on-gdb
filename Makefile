.PHONY: all tests clean
all:
	mkdir -p bin/
	g++ -std=c++17 -pedantic -Wall -ggdb -O0 -o bin/intset intset/*.cpp

_tests: all
	byexample -l shell --timeout 8  doctests/intset.md

tests:
	@make --no-print-directory _tests

clean:
	rm -f *.o bin/*

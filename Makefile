-include config.mk

CATCH ?= .
BUFFER_HANDLE ?= .

all: test run-test Makefile

run-test: test Makefile
	./$<

test: test.o Makefile
	g++ $< -o $@

test.o: test.cpp Makefile
	g++ -c $< -std=c++11 -MD -g -O0 -I $(CATCH) -I $(BUFFER_HANDLE) -I ../ -o $@

-include test.d

clean:
	rm -f test.d test.o test

-include config.mk

CATCH ?= .

all: test run-test Makefile

run-test: test Makefile
	./$<

test: test.o Makefile
	g++ $< -o $@

test.o: test.cpp Makefile
	g++ -c $< -std=c++14 -MD -g -O0 -I $(CATCH) -I ../ -o $@

-include test.d

clean:
	rm -f test.d test.o test

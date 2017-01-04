COMPILER = -std=c++14

all: helper.o monster.o citizen.o smalltown.o helper.o test.o
	g++ $(COMPILER) monster.o citizen.o smalltown.o test.o helper.o -o test
	./test

citizen.o: citizen.cc
	g++ $(COMPILER) -c citizen.cc

monster.o: monster.cc
	g++ $(COMPILER) -c monster.cc

smalltown.o: smalltown.h smalltown.cc
	g++ $(COMPILER) monster.o citizen.o -c smalltown.cc

test.o: test.cc
	g++ $(COMPILER) -c test.cc

helper.o: helper.cc helper.h
	g++ $(COMPILER) -c helper.cc
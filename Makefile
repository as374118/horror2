COMPILER = -std=c++11

all: helper.o monster.o citizen.o smalltown.o helper.o horror_example.o
	g++ $(COMPILER) monster.o citizen.o smalltown.o horror_example.o helper.o -o horror_example

citizen.o: citizen.cc
	g++ $(COMPILER) -c citizen.cc

monster.o: monster.cc
	g++ $(COMPILER) -c monster.cc

smalltown.o: smalltown.h smalltown.cc
	g++ $(COMPILER) monster.o citizen.o -c smalltown.cc

horror_example.o: horror_example.cc
	g++ $(COMPILER) -c horror_example.cc

helper.o: helper.cc helper.h
	g++ $(COMPILER) -c helper.cc
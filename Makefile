all: helper.o monster.o citizen.o smalltown.o helper.o horror_example.o
	g++ -std=gnu++11 monster.o citizen.o smalltown.o horror_example.o helper.o -o horror_example

citizen.o: citizen.cc
	g++ -std=gnu++11 -c citizen.cc

monster.o: monster.cc
	g++ -std=gnu++11 -c monster.cc

smalltown.o: smalltown.h smalltown.cc
	g++ -std=gnu++11 monster.o citizen.o -c smalltown.cc

horror_example.o: horror_example.cc
	g++ -std=gnu++11 -c horror_example.cc

helper.o: helper.cc helper.h
	g++ -std=gnu++11 -c helper.cc
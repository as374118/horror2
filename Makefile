all: helper.o monster.o citizen.o smalltown.o helper.o horror_example.o
	g++ -std=gnu++11 monster.o citizen.o smalltown.o horror_example.o helper.o -o horror_example

citizen.o: citizen.cc citizen.h helper.h
	g++ -std=gnu++11 -c citizen.cc

monster.o: monster.cc monster.h helper.h
	g++ -std=gnu++11 -c monster.cc

smalltown.o: monster.h citizen.h smalltown.h smalltown.cc helper.h
	g++ -std=gnu++11 monster.o citizen.o -c smalltown.cc

horror_example.o: monster.h citizen.h smalltown.h horror_example.cc
	g++ -std=gnu++11 -c horror_example.cc

helper.o: helper.cc helper.h
	g++ -std=gnu++11 -c helper.cc
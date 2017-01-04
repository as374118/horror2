#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include "citizen.h"
#include "monster.h"

void attack(MonsterOrGroup *, GroupOfCitizens *);

void attack(MonsterOrGroup *, GroupOfCitizens *);

class Status {
private:
	std::string monsterName;
	int aliveCitizens;
	HealthPoints monsterHealth;
	HealthPoints citizenHealth;
public:
	Status(std::string, int, HealthPoints, HealthPoints);

	std::string getMonsterName();
	int getAliveCitizens();
	HealthPoints getMonsterHealth();
	HealthPoints getCitizensHealth();
	void printStatus();

	bool isFinished();
	void printResult();
};

class SmallTown {
private:

	GroupOfCitizens * citizens = new GroupOfCitizens();
	MonsterOrGroup * evil = NULL;
	Time tCur = -1, tMax = -1; ;
	bool goodTimeForAttack();

public:
	SmallTown() {}

	// class for helping to build SmallTown
	class Builder;
	friend class Builder;

	void tick(Time);
	Status getStatus();
	void attack();
};

class SmallTown::Builder {
private:
	SmallTown * st = new SmallTown();
public:

	Builder();

	Builder monster(MonsterOrGroup *);
	Builder startTime(Time);
	Builder maxTime(Time);
	Builder citizen(Citizen *);

	SmallTown build();
};

#endif
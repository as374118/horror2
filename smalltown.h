#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include "monster.h"
#include "citizen.h"

void attack(MonsterOrGroup, GroupOfCitizens);

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

	bool isFinished();
	void printResult();
};

class SmallTown {
private:

	GroupOfCitizens citizens;
	MonsterOrGroup evil;
	Time tCur, t1; ;
	bool goodTimeForAttack();

public:

	class Builder;
	friend class SmallTown::Builder;

	SmallTown();
	SmallTown(GroupOfCitizens, MonsterOrGroup, Time, Time);

	void tick(Time);
	Status getStatus();
	void attack();
};

class SmallTown::Builder {
private:
	SmallTown *curTown;
public:

	Builder();

	Builder monster(MonsterOrGroup);
	Builder startTime(Time);
	Builder maxTime(Time);
	Builder citizen(Citizen);

	SmallTown build();
};


#endif
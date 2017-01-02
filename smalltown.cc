#include "smalltown.h"

void attack(MonsterOrGroup * monsters, GroupOfCitizens * citizens) {
	AttackPower monsterAttack = monsters->getAttackPower();
	AttackPower citizensAttack = citizens->getAttackPower();

	monsters->takeDamage(citizensAttack);
	citizens->takeDamage(monsterAttack);
}

Status::Status(std::string monsterName, int aliveCitizens,
		HealthPoints monsterHealth, HealthPoints citizenHealth) {
	this->monsterName = monsterName;
	this->aliveCitizens = aliveCitizens;
	this->monsterHealth = monsterHealth;
	this->citizenHealth = citizenHealth;
}

std::string Status::getMonsterName() {
	return this->monsterName;
}

int Status::getAliveCitizens() {
	return this->aliveCitizens;
}

HealthPoints Status::getMonsterHealth() {
	return this->monsterHealth;
}

HealthPoints Status::getCitizensHealth() {
	return this->citizenHealth;
}

bool Status::isFinished() {
	return this->monsterHealth == 0 || this->citizenHealth == 0;
}

void Status::printResult() {
	if (this->isFinished()) {

		HealthPoints monsterHealth = this->monsterHealth;
		HealthPoints citizenHealth = this->citizenHealth;

		if (monsterHealth == 0 && citizenHealth == 0) {
			puts("DRAW");
			return;
		}
		if (citizenHealth == 0) {
			puts("MONSTER WON");
			return;
		}
		puts("CITIZENS WON");

	} else {

		puts("Attack is going on...");

	}
}

SmallTown::SmallTown(GroupOfCitizens citizens,
	MonsterOrGroup evil, Time t0, Time t1) {
	this->citizens = citizens;
	this->evil = evil;
	this->tCur = t0;
	this->t1 = t1;
}

Status SmallTown::getStatus() {
	std::string monsterName = this->evil.getName();
	int aliveCitizens = this->citizens.getAlive();
	HealthPoints monsterHealth = this->evil.getHealth();
	HealthPoints citizenHealth = this->citizens.getHealth();

	Status res(monsterName, aliveCitizens, monsterHealth, citizenHealth);

	return res;
}

void SmallTown::attack() {
	MonsterOrGroup * evil = &(this->evil);
	GroupOfCitizens * citizens = &(this->citizens);
	::attack(evil, citizens);
}

bool SmallTown::goodTimeForAttack() {
	bool res = true;
	res &= this->tCur % 3 == 0;
	res |= this->tCur % 13 == 0;
	res &= this->tCur % 7 != 0;

	return res; 
}

void SmallTown::tick(Time t) {

	if (this->goodTimeForAttack()) {
		attack();
		if (this->getStatus().isFinished()) {
			this->getStatus().printResult();
		}
	}
	tCur += t;
	tCur %= this->t1; 
}


SmallTown::Builder::Builder() {
	curTown->citizens = GroupOfCitizens();
}

SmallTown::Builder SmallTown::Builder::monster(MonsterOrGroup evil) {
	curTown->evil = evil;
	return *this;
}

SmallTown::Builder SmallTown::Builder::startTime(Time t0) {
	curTown->tCur = t0;
	return *this;
}

SmallTown::Builder SmallTown::Builder::maxTime(Time t1) {
	curTown->t1 = t1;
	return *this;
}

SmallTown::Builder SmallTown::Builder::citizen(Citizen c) {
	curTown->citizens.add(c);
	return *this;
}

SmallTown SmallTown::Builder::build() {
	return *(curTown);
}
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

void Status::printStatus() {
	std::cout << "MonsterName: " << this->monsterName;
	std::cout << " citizensAlive: " << this->aliveCitizens;
	std::cout << " citizensHealth: " << this->citizenHealth;
	std::cout << " monsterHealth: " << this->monsterHealth;
	std::cout << std::endl; 
}

SmallTown::SmallTown() {
	this->citizens = new GroupOfCitizens();
	this->tMax = -1;
	this->tCur = -1;
	this->evil = NULL;
}

Status SmallTown::getStatus() {
	std::string monsterName = "";//this->evil->getName();
	int aliveCitizens = this->citizens->getAlive();
	HealthPoints monsterHealth = this->evil->getHealth();
	HealthPoints citizenHealth = this->citizens->getHealth();

	Status res(monsterName, aliveCitizens, monsterHealth, citizenHealth);

	return res;
}

void SmallTown::attack() {
	MonsterOrGroup * evil = this->evil;
	GroupOfCitizens * citizens = this->citizens;
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
	tCur %= (this->tMax + 1); 
}

SmallTown::Builder::Builder() {
	this->st = new SmallTown();
}

SmallTown::Builder SmallTown::Builder::monster(MonsterOrGroup m) {
	if (this->st->evil != NULL) {
		std::cerr << "Monster already set\n";
		throw  42;
	}
	this->st->evil = &m;
	return *this;
}

SmallTown::Builder SmallTown::Builder::citizen(Citizen c) {
	this->st->citizens->add(c);
	return *this;
}

SmallTown::Builder SmallTown::Builder::startTime(Time t0) {
	if (this->st->tCur != -1) {
		std::cerr << "Start time already set\n";
		throw 42;
	}
	this->st->tCur = t0;
	return *this;
}

SmallTown::Builder SmallTown::Builder::maxTime(Time tMax) {
	if (this->st->tMax != -1) {
		std::cerr << this->st->tMax << std::endl;
		std::cerr << "Max time already set\n";
		throw 42;
	}
	this->st->tMax = tMax;
	return *this;
}

SmallTown SmallTown::Builder::build() {
	bool ready = true;
	ready &= this->st->tCur >= 0;
	ready &= this->st->tMax >= 0;
	ready &= this->st->citizens != NULL;
	ready &= this->st->evil != NULL;
	if (!ready) {
		std::cerr << "Cannot build\n";
		throw 42;
	}
	return *(this->st);
}
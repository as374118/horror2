#include "smalltown.h"

// implementing attack function
// parameters: pointer to evil and pointer to GroupOfCitizens
// execute the attack
void attack(MonsterOrGroup * monsters, GroupOfCitizens * citizens) {
	AttackPower monsterAttack = monsters->getAttackPower();
	AttackPower citizensAttack = citizens->getAttackPower();
	// std::cout << "monsterAp: " << monsterAttack
	// std::cout << " citizenAp: " << citizensAttack << std::endl; 
	monsters->takeDamage(citizensAttack);
	citizens->takeDamage(monsterAttack);
}

// Status implementation
Status::Status(std::string monsterName, int aliveCitizens,
		HealthPoints monsterHealth, HealthPoints citizenHealth) {
	this->monsterName = monsterName;
	this->aliveCitizens = aliveCitizens;
	this->monsterHealth = monsterHealth;
	this->citizenHealth = citizenHealth;
}

// getters for Status
std::string Status::getMonsterName() {
	std::string res = std::string(this->monsterName);
	return res;
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

// Status functions for checking the result
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

// help  Status function for printing Status to stdout
void Status::printStatus() {
	std::cout << "MonsterName: " << this->monsterName;
	std::cout << " citizensAlive: " << this->aliveCitizens;
	std::cout << " citizensHealth: " << this->citizenHealth;
	std::cout << " monsterHealth: " << this->monsterHealth;
	std::cout << std::endl; 
}

// SmallTown implementation
Status SmallTown::getStatus() {
	std::string monsterName(this->evil->getName());
	int aliveCitizens = this->citizens->getAlive();
	HealthPoints monsterHealth = this->evil->getHealth();
	HealthPoints citizenHealth = this->citizens->getHealth();

	Status res(monsterName, aliveCitizens, monsterHealth, citizenHealth);

	return res;
}

void SmallTown::attack() {
	::attack(this->evil, this->citizens);
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
		this->attack();
		if (this->getStatus().isFinished()) {
			this->getStatus().printResult();
		}
	}

	// TODO
 	// to decide what variant should be used
	// if (t > 0)  {
	// 	this->tCur += 1;
	// 	this->tCur %= (this->tMax + 1);
	// 	this->tick(t - 1);
	// }

	this->tCur += t;
	this->tCur %= (this->tMax + 1);
}

// Builder implementation
SmallTown::Builder::Builder() {
	
}

SmallTown::Builder SmallTown::Builder::citizen(Citizen * c) {
	this->st->citizens->add(c);
	return *this;
}

SmallTown::Builder SmallTown::Builder::monster(MonsterOrGroup * m) {
	if (this->st->evil != NULL) {
		std::cerr << "Monster already set\n";
		throw  42;
	}

	this->st->evil = m;
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
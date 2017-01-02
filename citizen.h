#ifndef CITIZEN_H
#define CITIZEN_H

#include "helper.h"

class Citizen {
protected:
	virtual bool isAgeGood(Age);
	HealthPoints health;
	Age age;
public:
	Citizen(HealthPoints, Age);

	HealthPoints getHealth();
	Age getAge();
	void takeDamage(AttackPower);
};

class Attackable {
protected:
	AttackPower attackPower;
public:
	Attackable(AttackPower);

	AttackPower getAttackPower();
};


class Adult : public Citizen {
protected:
	// override
	bool isAgeGood(Age);
public:
	Adult(HealthPoints health, Age age) :
		Citizen(health, age) {
			if (!this->isAgeGood(age)) {
				throw 42;
			}
		}
};


class Teenager : public Citizen {
protected:
	// override
	bool isAgeGood(Age);
public:
	Teenager(HealthPoints health, Age age) :
		Citizen(health, age) {
			if (!this->isAgeGood(age)) {
				throw 42;
			}
		}
};


class Sheriff : public Adult, public Attackable {
public:
	Sheriff(HealthPoints health, Age age, AttackPower attackPower) :
		Adult(health, age), Attackable(attackPower) {}
};


class GroupOfCitizens {
private:
	std::vector<Citizen> casualCitizens;
	std::vector<Sheriff> sheriffs;
	HealthPoints health;
	int alive;
	AttackPower attackPower;

	void removeDead();
	HealthPoints countHealth();
	AttackPower countAttackPower();
public:
	GroupOfCitizens();
	

	void add(Citizen);
	void add(Sheriff);

	int getAlive();
	HealthPoints getHealth();
	AttackPower getAttackPower();

	void takeDamage(AttackPower);
};

// factory functions
Sheriff createSheriff(HealthPoints, Age, AttackPower);
Adult createAdult(HealthPoints, Age);
Teenager createTeenager(HealthPoints, Age);

#endif
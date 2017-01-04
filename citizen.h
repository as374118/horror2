#ifndef CITIZEN_H
#define CITIZEN_H

#include "helper.h"

class Citizen {
protected:
	virtual bool isAgeGood(Age) = 0;
	HealthPoints health;
	Age age;
public:
	Citizen(HealthPoints, Age);

	HealthPoints getHealth();
	Age getAge();
	virtual std::string toString() = 0;
	void takeDamage(AttackPower);
};

class Attackable {
protected:
	AttackPower attackPower;
public:
	Attackable(AttackPower ap);

	AttackPower getAttackPower();
	std::string toString();
};

class Adult : public Citizen {
protected:
	// override
	bool isAgeGood(Age);
public:
	Adult(HealthPoints health, Age age) :
		Citizen(health, age) {
			if (!this->isAgeGood(age)) {
				std::cerr << "Bad age for Adult\n";
				throw ERR_CODE;
			}
		}

	// override
	virtual std::string toString();
};

class Teenager : public Citizen {
protected:
	// override
	bool isAgeGood(Age);
public:
	Teenager(HealthPoints health, Age age) :
		Citizen(health, age) {
			if (!this->isAgeGood(age)) {
				std::cerr << "Bad age for teenager\n";
				throw ERR_CODE;
			}
		}

	// override
	std::string toString();
};

class Sheriff : public Adult, public Attackable {
public:
	Sheriff(HealthPoints health, Age age, AttackPower attackPower) :
		Adult(health, age), Attackable(attackPower) {}

	// Override
	std::string toString();
};

class GroupOfCitizens {
private:
	HealthPoints health;
	int alive;
	AttackPower attackPower;
	std::vector<Citizen *> citizens;

	void removeDead();
	HealthPoints countHealth();
	AttackPower countAttackPower();
public:
	GroupOfCitizens();
	
	void add(Citizen *);

	int getAlive();
	HealthPoints getHealth();
	AttackPower getAttackPower();
	void printCitizens();

	void takeDamage(AttackPower);
};


// factory functions
Sheriff * createSheriff(HealthPoints, Age, AttackPower);
Adult * createAdult(HealthPoints, Age);
Teenager * createTeenager(HealthPoints, Age);

#endif
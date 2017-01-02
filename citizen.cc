#include "citizen.h"

const BigInt MIN_AGE_ADULT = 18, MAX_AGE_ADULT = 100;
const BigInt MIN_AGE_TEENAGER = 11, MAX_AGE_TEENAGER = 18;

bool Citizen::isAgeGood(Age age) {
	return (age >= MIN_AGE_TEENAGER && age <= MAX_AGE_ADULT);
}

Citizen::Citizen(HealthPoints health, Age age) {
	if (!isAgeGood(age)) {
		printf("%lld\n", age);
		puts("ASS2");
		throw 42;
	}
	this->health = health;
	this->age = age;
}

HealthPoints Citizen::getHealth() {
	return this->health;
}

Age Citizen::getAge() {
	return this->age;
}

void Citizen::takeDamage(AttackPower damage) {
	this->health = max(0, this->health - damage);
}

Attackable::Attackable(AttackPower attackPower) {
	this->attackPower = attackPower;
}

AttackPower Attackable::getAttackPower() {
	return this->attackPower;
}

bool Teenager::isAgeGood(Age age) {
	return (age <= MAX_AGE_TEENAGER && age >= MIN_AGE_TEENAGER);
}

bool Adult::isAgeGood(Age age) {
	return (age <= MAX_AGE_ADULT && age >= MIN_AGE_ADULT);	
}

GroupOfCitizens::GroupOfCitizens() {
	this->alive = 0;
	this->health = 0;
	this->attackPower = 0;
}

void GroupOfCitizens::removeDead() {
	std::vector<Citizen> newCitizens;
	std::vector<Sheriff> newSheriffs;

	for (Citizen c : this->casualCitizens) {
		if (c.getHealth() > 0) {
			newCitizens.push_back(c);
		}
	}

	for (Sheriff s : this->sheriffs) {
		if (s.getHealth() > 0) {
			newSheriffs.push_back(s);
		}
	}

	this->sheriffs = newSheriffs;
	this->casualCitizens = newCitizens;
}

HealthPoints GroupOfCitizens::countHealth() {
	HealthPoints res = 0;

	for (Citizen c : this->casualCitizens) {
		res += c.getHealth();
	}

	for (Sheriff s : this->sheriffs) {
		res += s.getHealth();
	}

	return res;
}

AttackPower GroupOfCitizens::countAttackPower() {
	AttackPower res = 0;
	
	for (Sheriff s : this->sheriffs) {
		res += s.getAttackPower();
	}

	return res;
}

void GroupOfCitizens::add(Citizen c) {
	if (c.getHealth() > 0) {
		this->casualCitizens.push_back(c);
		this->health += c.getHealth();
		++this->alive;
	}
}

void GroupOfCitizens::add(Sheriff s) {
	if (s.getHealth() > 0) {
		this->sheriffs.push_back(s);
		this->health += s.getHealth();
		this->attackPower += s.getAttackPower();
		++this->alive;
	}
}

int GroupOfCitizens::getAlive() {
	return this->alive;
}

HealthPoints GroupOfCitizens::getHealth() {
	return this->health;
}

AttackPower GroupOfCitizens::getAttackPower() {
	return this->attackPower;
}

void GroupOfCitizens::takeDamage(AttackPower damage) {
	int alive = 0;

	for (Citizen c : this->casualCitizens) {
		c.takeDamage(damage);
		if (c.getHealth() > 0) {
			++alive;
		}
	}
	
	for (Sheriff s : this->sheriffs) {
		s.takeDamage(damage);
		if (s.getHealth() > 0) {
			++alive;
		}
	}

	if (this->alive != alive) {
		this->removeDead();
		this->alive = this->casualCitizens.size();
		this->alive += this->sheriffs.size();
		this->health = this->countHealth();
		this->attackPower = this->countAttackPower();
	}

}

Sheriff createSheriff(HealthPoints health, Age age, AttackPower ap) {
	return Sheriff(health, age, ap);
}

Adult createAdult(HealthPoints health, Age age) {
	return Adult(health, age);
}

Teenager createTeenager(HealthPoints health, Age age) {
	return Teenager(health, age);
}
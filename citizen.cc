#include "citizen.h"

const BigInt MIN_AGE_ADULT = 18, MAX_AGE_ADULT = 100;
const BigInt MIN_AGE_TEENAGER = 11, MAX_AGE_TEENAGER = 18;


// implementation of citizen
Citizen::Citizen(HealthPoints health, Age age) {
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

std::string Citizen::toString() {
	std::string res("");
	res += " health: " + std::to_string(this->health);
	res += " age: " + std::to_string(this->age);
	return res;
}

// implementation of attackable
Attackable::Attackable(AttackPower attackPower) {
	this->attackPower = attackPower;
}

AttackPower Attackable::getAttackPower() {
	return this->attackPower;
}

std::string Attackable::toString() {
	std::string res("");
	res += " attack: " + std::to_string(this->attackPower);
	return res;
}


// implementation of teenager
bool Teenager::isAgeGood(Age age) {
	return (age <= MAX_AGE_TEENAGER && age >= MIN_AGE_TEENAGER);
}

std::string Teenager::toString() {
	std::string res("Citizen ");
	res += Citizen::toString();
	return res;
}

// implementation of adult
bool Adult::isAgeGood(Age age) {
	return (age <= MAX_AGE_ADULT && age >= MIN_AGE_ADULT);	
}

std::string Adult::toString() {
	std::string res("Adult ");
	res += Citizen::toString();
	return res;
}

std::string Sheriff::toString() {
	std::string res("Sheriff ");
	res += Citizen::toString();
	res += Attackable::toString();
	return res;
}

// implementation of group of citizens
GroupOfCitizens::GroupOfCitizens() {
	this->alive = 0;
	this->health = 0;
	this->attackPower = 0;
	this->citizens = std::vector<Citizen *>();
}

void GroupOfCitizens::add(Citizen * c) {
	checkPointer(c, "Null citizen in GroupOfCitizens::add()");
	if (c->getHealth() > 0) {
		this->citizens.push_back(c);
		this->health += c->getHealth();
		++this->alive;

		// if citizen is a sherrif
		if (Sheriff * sh = dynamic_cast<Sheriff *>(c)) {
			this->attackPower += sh->getAttackPower();
		}
	} else {
		std::cerr << "Trying to add dead citizen to group";
		throw ERR_CODE;
	}
}

void GroupOfCitizens::removeDead() {
	std::vector<Citizen *> newCitizens;

	for (Citizen * c : this->citizens) {
		checkPointer(c, "Null citizen in removeDead()");
		if (c->getHealth() > 0) {
			newCitizens.push_back(c);
		}
	}

	this->citizens = newCitizens;
}

HealthPoints GroupOfCitizens::countHealth() {
	HealthPoints res = 0;

	for (Citizen * c : this->citizens) {
		checkPointer(c, "Null citizen in countHealth()");
		res += c->getHealth();
	}

	return res;
}

AttackPower GroupOfCitizens::countAttackPower() {
	AttackPower res = 0;
	
	for (Citizen * c : this->citizens) {
		checkPointer(c, "Null citizen in countAttackPower()");
		if (Sheriff * s = dynamic_cast<Sheriff *>(c))  {
			res += s->getAttackPower();
		}
	}

	return res;
}

void GroupOfCitizens::takeDamage(AttackPower damage) {
	int alive = 0;
	HealthPoints newHealth = 0;

	for (Citizen * c : this->citizens) {
		checkPointer(c, "Null citizen in takeDamage()");
		c->takeDamage(damage);
		if (c->getHealth() > 0) {
			++alive;
			newHealth += c->getHealth();
		}
	}

	if (this->alive != alive) {
		this->removeDead();
		this->alive = this->citizens.size();
		this->health = this->countHealth();
		this->attackPower = this->countAttackPower();
	} else {
		this->health = newHealth;
	}
}

// getters
int GroupOfCitizens::getAlive() {
	return this->alive;
}

HealthPoints GroupOfCitizens::getHealth() {
	return this->health;
}

AttackPower GroupOfCitizens::getAttackPower() {
	return this->attackPower;
}

// help function which prints group of citizens
void GroupOfCitizens::printCitizens() {
	puts("//////////GROUP OF CITIZENS//////////////");
	puts("Citizens:");
	for (Citizen * c : this->citizens) {
		checkPointer(c, "Null citizen in printCitizens()");
		std::cout << c->toString() << std::endl;
	}
	puts("//////////////////////////////////////////");
}

// factory functions
Sheriff * createSheriff(HealthPoints hp, Age age, AttackPower ap) {
	return new Sheriff(hp, age, ap);
}

Adult * createAdult(HealthPoints hp, Age age) {
	return new Adult(hp, age);
}

Teenager * createTeenager(HealthPoints hp, Age age) {
	return new Teenager(hp, age);
}
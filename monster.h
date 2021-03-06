#ifndef MONSTER_H
#define MONSTER_H

#include "helper.h"

class MonsterOrGroup {
protected:
	HealthPoints health;
	AttackPower attackPower;

public:
	MonsterOrGroup(HealthPoints, AttackPower);

	HealthPoints getHealth();
	AttackPower getAttackPower();
	virtual std::string getName() = 0;
	virtual void takeDamage(AttackPower) = 0;
};

class Monster : public MonsterOrGroup {
public:
	Monster(HealthPoints hp, AttackPower ap) : MonsterOrGroup(hp, ap) {}

	// override
	void takeDamage(AttackPower);
};

class Zombie : public Monster {
public:
	Zombie(HealthPoints hp, AttackPower ap) : Monster(hp, ap) {}

	// override
	std::string getName();
};

class Vampire : public Monster {
public:
	Vampire(HealthPoints hp, AttackPower ap) : Monster(hp, ap) {}

	// override
	std::string getName();
};

class Mummy : public Monster {
public:
	Mummy(HealthPoints hp, AttackPower ap) : Monster(hp, ap) {}

	// override
	std::string getName();
};

class GroupOfMonsters : public MonsterOrGroup {
private:

	std::vector<Monster *> monsters;
	int alive = 0;

	HealthPoints static countHealth(std::vector<Monster *>);
	AttackPower static countAttackPower(std::vector<Monster *>);

	void removeDeadMonsters();
public:
	GroupOfMonsters(std::vector<Monster *> monsters) :
		MonsterOrGroup(countHealth(monsters), countAttackPower(monsters)) {
			this->monsters = std::vector<Monster *>(monsters);;
			this->alive = this->monsters.size();
		}
	GroupOfMonsters(std::initializer_list<Monster *> monsters) :
		GroupOfMonsters(std::vector<Monster *>(monsters)) {}

	void takeDamage(AttackPower damage);
	int getAlive();

	std::string getName();
};

// factory functions
Zombie * createZombie(HealthPoints, AttackPower);
Vampire * createVampire(HealthPoints, AttackPower);
Mummy * createMummy(HealthPoints, AttackPower);
// GroupOfMonsters * createGroupOfMonsters(std::vector<Monster *>);
GroupOfMonsters * createGroupOfMonsters(std::vector<Monster *, std::allocator<Monster *>>);

#endif
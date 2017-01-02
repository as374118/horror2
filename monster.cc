#include "monster.h"

// methods of MonsterOrGroup class
MonsterOrGroup::MonsterOrGroup() {
	this->health = 0;
	this->attackPower = 0;
}

MonsterOrGroup::MonsterOrGroup(HealthPoints health, AttackPower attackPower) {
	this->health = health;
	this->attackPower = attackPower;
}

HealthPoints MonsterOrGroup::getHealth() {
	return this->health;
}

AttackPower MonsterOrGroup::getAttackPower() {
	return this->attackPower;
}

void Monster::takeDamage(AttackPower damage) {
	MonsterOrGroup::health = max(0, MonsterOrGroup::health - damage);
}

std::string Vampire::getName() {
	return "Vampire";
}

std::string Zombie::getName() {
	return "Zombie";
}

std::string Mummy::getName() {
	return "Mummy";
}


// methods of group of monster class

void GroupOfMonsters::removeDeadMonsters() {
	std::vector<Monster> newMonsters;
	int newAlive = 0;
	HealthPoints newHealth = 0;
	AttackPower newAttackPower = 0;

	for (Monster m : this->monsters) {
		if (m.getHealth() > 0) {
			newAlive++;
			newHealth += m.getHealth();
			newAttackPower += m.getAttackPower();
			newMonsters.push_back(m);
		}
	}

	this->alive = newAlive;
	MonsterOrGroup::health = newHealth;
	MonsterOrGroup::attackPower = newAttackPower;
}

HealthPoints GroupOfMonsters::countHealth(std::vector<Monster> monsters) {
	HealthPoints res = 0;

	for (Monster m : monsters) {
		res += m.getHealth();
	}

	return res;
}

AttackPower GroupOfMonsters::countAttackPower(std::vector<Monster> monsters) {
	AttackPower res = 0;

	for (Monster m : monsters) {
		res += m.getAttackPower();
	}

	return res;
}

void GroupOfMonsters::takeDamage(AttackPower damage) {
	HealthPoints newHealth = 0;
	int newAlive = 0;

	for (Monster m : this->monsters) {
		m.takeDamage(damage);
		if (m.getHealth() > 0) {
			newHealth += m.getHealth();
			newAlive++;
		}
	}

	if (this->alive != newAlive) {
		removeDeadMonsters();
		MonsterOrGroup::health = countHealth(this->monsters);
		MonsterOrGroup::attackPower = countAttackPower(this->monsters);
	} else {
		MonsterOrGroup::health = newHealth;
	}
}

int GroupOfMonsters::getAlive() {
	return this->alive;
}

std::string GroupOfMonsters::getName() {
	return "GroupOfMonsters";
}

Zombie createZombie(HealthPoints hp, AttackPower ap) {
	return Zombie(hp, ap);
}

Vampire createVampire(HealthPoints hp, AttackPower ap) {
	return Vampire(hp, ap);
}

Mummy createMummy(HealthPoints hp, AttackPower ap) {
	return Mummy(hp, ap);
}

// TODO
GroupOfMonsters createGroupOfMonsters(std::vector<Monster> &monsters) {
	return GroupOfMonsters(monsters);
}

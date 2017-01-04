#include "monster.h"

// implementing abstract class MonsterOrGroup
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

// implementing abstract class Monster
void Monster::takeDamage(AttackPower damage) {
	MonsterOrGroup::health = max(0, MonsterOrGroup::health - damage);
}

// implementing Vampire
std::string Vampire::getName() {
	return "Vampire";
}


// implementing Zombie
std::string Zombie::getName() {
	return "Zombie";
}

// implementing Mummy
std::string Mummy::getName() {
	return "Mummy";
}

// implementing GroupOfMonsters
void GroupOfMonsters::removeDeadMonsters() {
	std::vector<Monster *> newMonsters;
	int newAlive = 0;
	HealthPoints newHealth = 0;
	AttackPower newAttackPower = 0;

	for (Monster * m : this->monsters) {
		checkPointer(m, "Null monster in removeDeadMonsters()");
		if (m->getHealth() > 0) {
			newAlive++;
			newHealth += m->getHealth();
			newAttackPower += m->getAttackPower();
			newMonsters.push_back(m);
		}
	}

	this->alive = newAlive;
	this->monsters = newMonsters;
	MonsterOrGroup::health = newHealth;
	MonsterOrGroup::attackPower = newAttackPower;

}

HealthPoints GroupOfMonsters::countHealth(std::vector<Monster *> monsters) {
	HealthPoints res = 0;

	for (Monster * m : monsters) {
		checkPointer(m, "Null monster in countHealth()");
		res += m->getHealth();
	}

	return res;
}

AttackPower GroupOfMonsters::countAttackPower(std::vector<Monster * > monsters) {
	AttackPower res = 0;

	for (Monster * m : monsters) {
		checkPointer(m, "Null monster in countAttackPower()");
		res += m->getAttackPower();
	}

	return res;
}

void GroupOfMonsters::takeDamage(AttackPower damage) {
	HealthPoints newHealth = 0;
	int newAlive = 0;

	for (Monster * m : this->monsters) {
		m->takeDamage(damage);
		if (m->getHealth() > 0) {
			newHealth += m->getHealth();
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

// getters
int GroupOfMonsters::getAlive() {
	return this->alive;
}

std::string GroupOfMonsters::getName() {
	return std::string("GroupOfMonsters");
}


// factory functions
Zombie * createZombie(HealthPoints hp, AttackPower ap) {
	return new Zombie(hp, ap);
}

Vampire * createVampire(HealthPoints hp, AttackPower ap) {
	return new Vampire(hp, ap);
}

Mummy * createMummy(HealthPoints hp, AttackPower ap) {
	return new Mummy(hp, ap);
}

// GroupOfMonsters * createGroupOfMonsters(std::vector<Monster *> monsters) {
// 	return new GroupOfMonsters(monsters);
// }

GroupOfMonsters * createGroupOfMonsters(
	std::vector<Monster *, std::allocator<Monster *>> monsters) {
	return new GroupOfMonsters(monsters);
}
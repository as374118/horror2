#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include <cassert>

void testCitizen() {
	// testing group of monsters
    GroupOfCitizens g = GroupOfCitizens();
    g.add(createTeenager(100, 13));
    g.add(createSheriff(150, 20, 20));
    g.add(createAdult(200, 25));
    assert(g.getAttackPower() == 20);
    assert(g.getAlive() == 3);
    // g.printCitizens();
    g.takeDamage(170);
    // g.printCitizens();
    assert(g.getAlive() == 1);
    assert(g.getAttackPower() == 0);

}

void testMonster() {
	// test group of monsters
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });
    assert(groupOfMonsters->getHealth() == 140);
    assert(groupOfMonsters->getAttackPower() == 3);
    groupOfMonsters->takeDamage(21);
    assert(groupOfMonsters->getHealth() == 78);
    assert(groupOfMonsters->getAttackPower() == 2);
}

void testSmallTown() {
	auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });
    auto smallTown = SmallTown::Builder()
        .monster(groupOfMonsters)
        .startTime(3)
        .maxTime(27)
        .citizen(createSheriff(100, 35, 20))
        .citizen(createAdult(100, 21))
        .citizen(createTeenager(50, 14))
        .build();

    smallTown.tick(18);
    smallTown.tick(3);

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 80);
    assert(status.getAliveCitizens() == 3);
}

int main() {
	testCitizen();
	testMonster();
	testSmallTown();

	std::cout << "OK!\n";

	return 0;
}
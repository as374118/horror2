//
//  horror_example.cc
//  horror-movie-2
//
//  Created by Patrycja Wegrzynowicz on 12/10/16.
//  Copyright (c) 2016 Patrycja Wegrzynowicz. All rights reserved.
//

#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include <cassert>

int main(int argc, const char * argv[]) {
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });

    // test group of citizens
    GroupOfCitizens g = GroupOfCitizens();
    g.add(createTeenager(100, 13));
    g.add(createSheriff(150, 20, 20));
    g.add(createAdult(200, 25));
    // assert(g.getAttackPower() == 20);
    // assert(g.getAlive() == 3);
    // // g.printCitizens();
    // g.takeDamage(170);
    // // g.printCitizens();
    // assert(g.getAlive() == 1);
    // assert(g.getAttackPower() == 0);

    // test group of monsters
    // assert(groupOfMonsters.getHealth() == 140);
    // assert(groupOfMonsters.getAttackPower() == 3);
    // groupOfMonsters.takeDamage(21);
    // assert(groupOfMonsters.getHealth() == 78);
    // assert(groupOfMonsters.getAttackPower() == 2);

    // test smallTown
    auto bld = SmallTown::Builder();
    bld = bld.monster(groupOfMonsters);
    bld = bld.startTime(3);
    bld = bld.maxTime(27);
    bld = bld.citizen(createSheriff(100, 35, 20));
    bld = bld.citizen(createAdult(100, 21));
    bld = bld.citizen(createTeenager(50, 14));
    SmallTown smallTown = bld.build();

    smallTown.getStatus().printStatus();
    // smallTown.tick(18);
    // smallTown.tick(3);

    // auto status = smallTown.getStatus();
    // assert(status.getMonsterName() == "GroupOfMonsters");
    // assert(status.getMonsterHealth() == 80);
    // assert(status.getAliveCitizens() == 3);

    puts("OK!");

    return 0;
}
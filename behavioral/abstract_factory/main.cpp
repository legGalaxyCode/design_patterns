#include "factory.hpp"

#include <iostream>

void clientCode(const AbstractWeaponFactory& factory) {
    auto sword = factory.createSword();
    auto stuff = factory.createStuff();

    std::cout << "Sword damage type - " << sword->damageType() << '\n';
    std::cout << "Stuff damage type - " << stuff->damageType() << '\n';
    std::cout << "Total damage = " << sword->damage() + stuff->damage() << '\n';
}

int main() {
    std::cout << "Hello, abstract factory pattern!\n";

    auto bronzeWeaponMaster = std::make_unique<BronzeWeaponFactory>();
    auto goldWeaponMaster = std::make_unique<GoldWeaponFactory>();

    // pass concrete realization
    clientCode(*bronzeWeaponMaster);
    clientCode(*goldWeaponMaster);

    return 0;
}

#include "builder.hpp"

#include <iostream>

void clientCode(Director& director) {
    auto woodenBuilder = std::make_shared<WoodenHouseBuilder>();
    director.setBuilder(woodenBuilder);
    director.buildMinimumHouse();

    // get not ready wooden house
    auto house = woodenBuilder->getHouse();
    std::cout << *house;

    director.buildFullHouse();

    // get ready wooden house
    house = woodenBuilder->getHouse();
    std::cout << *house;

    // change builder to another
    auto steelBuilder = std::make_shared<SteelHouseBuilder>();
    director.setBuilder(steelBuilder);
    director.buildMinimumHouse();

    // do the same as for wooden house
    house = steelBuilder->getHouse();
    std::cout << *house;

    director.buildFullHouse();

    house = steelBuilder->getHouse();
    std::cout << *house;

    // remember that Director is optional!
}

int main() {
    std::cout << "Hello, builder pattern!\n";

    auto director = std::make_unique<Director>();
    clientCode(*director);

    return 0;
}
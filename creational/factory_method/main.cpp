#include "factory_method.hpp"

void clientCode(const Blacksmith& blacksmith) {
    blacksmith.demonstrateSword();
}

int main() {
    std::cout << "Hello, factory method pattern!\n";

    auto juniorBlacksmith = std::make_unique<JuniorBlacksmith>();
    auto seniorBlacksmith = std::make_unique<SeniorBlacksmith>();

    // pass concrete realization
    clientCode(*juniorBlacksmith);
    clientCode(*seniorBlacksmith);

    return 0;
}
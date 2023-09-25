#include "prototype.hpp"

void clientCode(proto::PrototypeFactory& factory) {
    std::cout << "Create prototype 1\n";
    auto proto1 = factory.createPrototype(proto::PrototypeFactory::PROTOTYPE_1);
    proto1->setValue(11);

    std::cout << "Create prototype 2\n";
    auto proto2 = factory.createPrototype(proto::PrototypeFactory::PROTOTYPE_2);
    proto2->setValue(22);
}

int main() {
    std::cout << "Hello, prototype pattern!\n";

    auto factory = std::make_unique<proto::PrototypeFactory>();
    clientCode(*factory);

    return 0;
}
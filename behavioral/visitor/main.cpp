#include "visitor.hpp"

int main() {
    Dog dog(AnimalType::Dog);
    Cat cat(AnimalType::Cat);
    Monkey monkey(AnimalType::Monkey);

    AnimalVisitor visitor;
    visitor.visit(dog);
    visitor.visit(cat);
    visitor.visit(monkey);

    return 0;
}
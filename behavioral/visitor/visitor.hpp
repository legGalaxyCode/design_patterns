#include <iostream>

enum class AnimalType {
    Dog,
    Cat,
    Monkey
};

class Animal {
public:
    explicit Animal(AnimalType t): type_(t) {}
    virtual ~Animal() = 0;


    AnimalType getType() const { return type_; }

private:
    AnimalType type_;
};

Animal::~Animal() {}

class Dog : public Animal {
public:
    explicit Dog(AnimalType t): Animal(t) {}
    virtual ~Dog() {}

    void sound() const { std::cout << "dog's sound\n"; }
};

class Cat : public Animal {
public:
    explicit Cat(AnimalType t): Animal(t) {}
    virtual ~Cat() {}

    void petting() const { std::cout << "pet a cat\n"; }
};

class Monkey : public Animal {
public:
    explicit Monkey(AnimalType t): Animal(t) {}
    virtual ~Monkey() {}

    void giveBanana() const { std::cout << "monkey got a banana\n"; }
};

class AnimalVisitor {
public:
    void visit(Animal& animal) {
        switch (animal.getType()) {
            default:
                throw std::runtime_error("Unknown type!");
                break;
            case AnimalType::Dog:
                return visitDog(static_cast<Dog&>(animal));
            case AnimalType::Cat:
                return visitCat(static_cast<Cat&>(animal));
            case AnimalType::Monkey:
                return visitMonkey(static_cast<Monkey&>(animal));
        }
    }
    void visitDog(Dog& dog) {
        std::cout << "visit dog\n";
        dog.sound();
    };
    void visitCat(Cat& cat) {
        std::cout << "visit cat\n";
        cat.petting();
    };
    void visitMonkey(Monkey& monkey) {
        std::cout << "visit monkey\n";
        monkey.giveBanana();
    };
};
#include <memory>
#include <iostream>
#include <unordered_map>
#include <utility>

// Паттерн Прототип
//
// Назначение: Позволяет копировать объекты, не вдаваясь в подробности их
// реализации.

namespace proto {
    class Prototype;
    using PrototypePtr = std::unique_ptr<Prototype>;

    class Prototype {
    public:
        Prototype() = default;
        explicit Prototype(std::string name): protoName_(std::move(name)) {}
        virtual ~Prototype() = default;

        virtual PrototypePtr clone() const = 0;
        virtual void setValue(uint32_t value) {
            protoValue_ = value;
            std::cout << "Call value setter from " << protoName_ << " with value = " << protoValue_ << '\n';
        }

    protected:
        std::string protoName_;
        uint32_t protoValue_ = 0;
    };

    class ConcretePrototype1 : public Prototype {
    public:
        ConcretePrototype1(std::string name, uint32_t value):
            Prototype(std::move(name)), concreteProtoValue1_(value) {}

        PrototypePtr clone() const override { return std::make_unique<ConcretePrototype1>(*this); }
    private:
        uint32_t concreteProtoValue1_;
    };

    class ConcretePrototype2 : public Prototype {
    public:
        ConcretePrototype2(std::string name, uint32_t value):
                Prototype(std::move(name)), concreteProtoValue2_(value) {}

        PrototypePtr clone() const override { return std::make_unique<ConcretePrototype2>(*this); }
    private:
        uint32_t concreteProtoValue2_;
    };

    /**
     * In PrototypeFactory you have two concrete prototypes, one for each concrete
     * prototype class, so each time you want to create a bullet , you can use the
     * existing ones and clone those.
     */
     // optional factory
     class PrototypeFactory {
     public:
         enum Type {
             PROTOTYPE_1 = 1,
             PROTOTYPE_2
         };
         PrototypeFactory() {
             prototypes_[Type::PROTOTYPE_1] = std::make_unique<ConcretePrototype1>("PROTOTYPE_1 ", 10);
             prototypes_[Type::PROTOTYPE_2] = std::make_unique<ConcretePrototype2>("PROTOTYPE_2 ", 20);
         }

         /**
          * Notice here that you just need to specify the type of the prototype you
          * want and the method will create from the object with this type.
          */
         PrototypePtr createPrototype(Type type) {
             return prototypes_[type]->clone();
         }
     private:
         std::unordered_map<Type, PrototypePtr> prototypes_;
     };
}

// In C++ you can use this pattern to implement virtual copy constructor
// and virtual constructor

namespace vc {
    struct Animal;
    using AnimalPtr = std::unique_ptr<Animal>;
    using CAnimalPtr = const std::unique_ptr<Animal>;

    struct Animal {
        virtual ~Animal() = default;
        // define virtual constructor
        virtual AnimalPtr create() = 0;
        virtual CAnimalPtr create() const = 0;
        // define virtual copy constructor
        virtual AnimalPtr clone() = 0;
        virtual CAnimalPtr clone() const = 0;
    };

    struct Dog : public Animal {
        AnimalPtr create() override { return std::make_unique<Dog>(); }
        CAnimalPtr create() const override { return std::make_unique<Dog>(); }
        AnimalPtr clone() override { return std::make_unique<Dog>(*this); }
        CAnimalPtr clone() const override { return std::make_unique<Dog>(*this); }
    };

    struct Cat : public Animal {
        AnimalPtr create() override { return std::make_unique<Cat>(); }
        CAnimalPtr create() const override { return std::make_unique<Cat>(); }
        AnimalPtr clone() override { return std::make_unique<Cat>(*this); }
        CAnimalPtr clone() const override { return std::make_unique<Cat>(*this); }
    };
}
#include <memory>
#include <iostream>

enum DamageType {
    PHYSICAL = 1,
    MAGICAL
};

class Weapon {
public:
    virtual uint32_t damage() const = 0;
    virtual DamageType damageType() const = 0;
    virtual ~Weapon(){};
};

class Sword : public Weapon {
public:
    // all swords have a physical damage type
    DamageType damageType() const override {
        return DamageType::PHYSICAL;
    }
    // possible another sword-specific stuff can be added
};

class BronzeSword : public Sword {
public:
    uint32_t damage() const override {
        return 1;
    }
};

class GoldSword : public Sword {
public:
    uint32_t damage() const override {
        return 3;
    }
};

using SwordPtr = std::unique_ptr<Sword>;

class Blacksmith {
public:
    virtual ~Blacksmith(){}
    virtual SwordPtr createSword() const = 0;
    /**
   * Также заметьте, что, несмотря на название, основная обязанность Создателя
   * не заключается в создании продуктов. Обычно он содержит некоторую базовую
   * бизнес-логику, которая основана на объектах Продуктов, возвращаемых
   * фабричным методом. Подклассы могут косвенно изменять эту бизнес-логику,
   * переопределяя фабричный метод и возвращая из него другой тип продукта.
   */
   virtual void demonstrateSword() const {
       auto sword = createSword();
       std::cout << "This sword has " << sword->damage() << " damage!\n";
   }
};

class JuniorBlacksmith : public Blacksmith {
public:
    SwordPtr createSword() const override {
        return std::make_unique<BronzeSword>();
    }
};

class SeniorBlacksmith : public Blacksmith {
    SwordPtr createSword() const override {
        return std::make_unique<GoldSword>();
    }
};
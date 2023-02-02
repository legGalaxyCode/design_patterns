#include <memory>

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

class Stuff : public Weapon {
public:
    // all stuffs have a physical damage type
    DamageType damageType() const override {
        return DamageType::MAGICAL;
    }
    // possible another stuff-specific stuff can be added
};

class BronzeStuff : public Stuff {
public:
    uint32_t damage() const override {
        return 2;
    }
};

class GoldStuff : public Stuff {
public:
    uint32_t damage() const override {
        return 4;
    }
};

class AbstractWeaponFactory {
public:
    virtual inline std::unique_ptr<Sword> createSword() const = 0;
    virtual inline std::unique_ptr<Stuff> createStuff() const = 0;
};

class BronzeWeaponFactory : public AbstractWeaponFactory {
public:
    std::unique_ptr<Sword> createSword() const override {
        return std::make_unique<BronzeSword>();
    }
    std::unique_ptr<Stuff> createStuff() const override {
        return std::make_unique<BronzeStuff>();
    }
};

class GoldWeaponFactory : public AbstractWeaponFactory {
public:
    std::unique_ptr<Sword> createSword() const override {
        return std::make_unique<GoldSword>();
    }
    std::unique_ptr<Stuff> createStuff() const override {
        return std::make_unique<GoldStuff>();
    }
};